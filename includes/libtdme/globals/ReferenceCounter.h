/**
 * @version $Id: 7e9a09e29495c44188f430db0b36df8b1eee72cb $
 */

#ifndef TDME_GLOBAL_REFERENCECOUNTER_H
#define TDME_GLOBAL_REFERENCECOUNTER_H

namespace TDMEGlobal {

	/**
	 * Reference counter implementation which should be used with inheritance
	 * @author Andreas Drewke
	 */
	class ReferenceCounter {
		public:
			/**
			 * @brief Public constructor
			 */
			ReferenceCounter();

			/**
			 * @brief destructor
			 */
			virtual ~ReferenceCounter();

			/**
			 * @brief acquires a reference, incrementing the counter
			 */
			void acquireReference();

			/**
			 * @brief releases a reference, thus decrementing the counter and delete it if reference counter is zero
			 */
			void releaseReference();
		private:
			int referenceCounter;
	};

};

#endif
