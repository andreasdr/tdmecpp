/**
 * @version $Id: 328b0c9d22e88ecf229407ac60be7552b803cc05 $
 */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <libtdme/network/shared/NIOTCPSocket.h>

using namespace TDMENetwork;

/**
 * @brief public destructor
 */
NIOTCPSocket::~NIOTCPSocket() {
}

size_t NIOTCPSocket::read(void* buf, const size_t bytes) throw (NIOIOException) {
	ssize_t bytesRead = ::recv(descriptor, buf, bytes, 0);
	if (bytesRead == -1) {
		std::string msg = "error while reading from socket: ";
		msg+= strerror(errno);
		throw NIOIOException(msg);
	} else
	if (bytesRead == 0) {
		throw NIOIOSocketClosedException("end of stream");
	}
	//
	return (size_t)bytesRead;
}

size_t NIOTCPSocket::write(void* buf, const size_t bytes) throw (NIOIOException) {
	#ifdef __APPLE__
		ssize_t bytesWritten = ::send(descriptor, buf, bytes, 0);
	#else
		ssize_t bytesWritten = ::send(descriptor, buf, bytes, MSG_NOSIGNAL);
	#endif
	if (bytesWritten == -1) {
		if (errno == ECONNRESET || errno == EPIPE) {
			std::string msg = "end of stream: ";
			msg+= strerror(errno);
			throw NIOIOSocketClosedException(msg);
		} else {
			std::string msg = "error while writing to socket: ";
			msg+= strerror(errno);
			throw NIOIOException(msg);
		}
	}
	//
	return (size_t)bytesWritten;
}

void NIOTCPSocket::create(NIOTCPSocket& socket) throw (NIOSocketException) {
	socket.descriptor = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket.descriptor == -1) {
		std::string msg = "Could not create socket: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}
	#ifdef __APPLE__
		int flag = 1;
		if (setsockopt(socket.descriptor, SOL_SOCKET, SO_NOSIGPIPE, (void*)&flag, sizeof(flag)) == -1) {
			std::string msg = "Could not set no sig pipe on socket: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}
	#endif
}

void NIOTCPSocket::createServerSocket(NIOTCPSocket& socket, const std::string& ip, const unsigned int port, const int backlog) throw (NIOSocketException) {
	// create socket
	NIOTCPSocket::create(socket);

	try {
		// set non blocked
		socket.setNonBlocked();

		// bind
		socket.bind(ip, port);

		// make socket listen, backlog is 10% of max CCU
		if (listen(socket.descriptor, backlog) == -1) {
			std::string msg = "Could not set socket to listen: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}
	} catch (NIOSocketException &exception) {
		socket.close();
		throw;
	}
}

void NIOTCPSocket::setTCPNoDelay() throw (NIOSocketException) {
	int flag = 1;
	if (setsockopt(descriptor, IPPROTO_TCP, TCP_NODELAY, (void*)&flag, sizeof(flag)) == -1) {
		std::string msg = "Could not set tcp no delay: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}
}

bool NIOTCPSocket::accept(NIOTCPSocket &_socket) throw (NIOSocketException) {
	struct sockaddr_in _sin;
	socklen_t _sinSize = sizeof(_sin);

	// accept socket
	int _descriptor = ::accept(descriptor, (struct sockaddr *)&_sin, &_sinSize);
	if (_descriptor == -1) {
		// no more connections are present
		if (errno == EAGAIN ||
			errno == EWOULDBLOCK) {
			return false;
		}
		std::string msg = "Could not accept socket: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}

	// create client socket, return it
	_socket.descriptor = _descriptor;
	_socket.ip = inet_ntoa(_sin.sin_addr);
	_socket.port = ntohs(_sin.sin_port);
	_socket.setNonBlocked();
	_socket.setTCPNoDelay();

	// success
	return true;
}
