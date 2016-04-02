/**
 * @version $Id: 40dda42c96649801d8be726305585cb06424ca21 $
 */

#include <exception>
#include <typeinfo>

#include <libtdme/globals/RTTI.h>
#include <libtdme/globals/Logger.h>
#include <libtdme/network/shared/NIOServerClient.h>
#include <libtdme/network/shared/NIOServerGroup.h>
#include <libtdme/network/shared/NIOServerWorkerThread.h>

using namespace TDMENetwork;

NIOServerWorkerThread::NIOServerWorkerThread(const unsigned int id, NIOServerWorkerThreadPool* threadPool) :
	TDMEThreading::Thread("nioworkerthread"),
	id(id),
	threadPool(threadPool) {
	//
}

NIOServerWorkerThread::~NIOServerWorkerThread() {
}

void NIOServerWorkerThread::run() {
	Logger::log(
		Logger::LEVEL_INFO,
		"ServerWorkerThread[%u]::run(): start",
		id
	);

	// wait on startup barrier
	threadPool->startUpBarrier->wait();

	NIOServerRequest* request;
	while((request = threadPool->getElement()) != NULL) {
		// get request parameter
		NIOServerRequest::RequestType requestType = request->getRequestType();
		NIOServerClient* client = NULL;
		NIOServerGroupBase* group = NULL;

		// handle request types
		switch(requestType) {
			case(NIOServerRequest::REQUESTTYPE_CLIENT_REQUEST): {
				client = (NIOServerClient*)request->getObject();
				stringstream* frame = request->getMessageFrame();
				uint32_t messageId = request->getMessageId();
				uint8_t retries = request->getMessageRetries();

				// handle request
				try {
					client->onRequest(frame, messageId, retries);
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): request: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);

					// unhandled exception, so shutdown the client
					client->shutdown();
				}

				// delete stream
				delete frame;

				//
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_CLIENT_INIT): {
				client = (NIOServerClient*)request->getObject();
				// handle close
				try {
					client->onInit();
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): close: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);
				}
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_CLIENT_CLOSE): {
				client = (NIOServerClient*)request->getObject();
				// handle close
				try {
					client->onClose();
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): close: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);
				}
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_CLIENT_CUSTOM): {
				client = (NIOServerClient*)request->getObject();
				// handle close
				try {
					client->onCustom(request->getCustomEvent());
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): close: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);
				}
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_GROUP_INIT): {
				group = (NIOServerGroupBase*)request->getObject();
				// handle close
				try {
					group->onInit();
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): close: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);
				}
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_GROUP_CLOSE): {
				group = (NIOServerGroupBase*)request->getObject();
				// handle close
				try {
					group->onClose();
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): close: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);
				}
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_GROUP_CUSTOM): {
				group = (NIOServerGroupBase*)request->getObject();
				// handle close
				try {
					group->onCustomEvent(request->getCustomEvent());
				} catch(exception& exception) {
					Logger::log(
						Logger::LEVEL_WARNING,
						"ServerWorkerThread[%i]::run(): close: %s: %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
						exception.what()
					);
				}
				break;
			}
		}

		// release reference
		if (client != NULL) client->releaseReference();
		if (group != NULL) group->releaseReference();

		// delete request
		delete(request);
	}

	//
	Logger::log(
		Logger::LEVEL_INFO,
		"ServerWorkerThread[%u]::run(): done",
		id
	);
}
