#pragma once

#include "StarWarsAPI.h"
#include "PrintableObject.h"
#include "GlabalNames.h"
#include "Semaphore.h"

namespace StarWarsSystem
{
	class StarWarsObject ReadWriteLockObject : public PrintableObject
	{
	protected:
		Core::Semaphore* _e, *_w, *_r;
		void Estafeta()
		{
			if ((NUM_R == 0) && (NUM_W == 0) && (WAIT_W > 0))
			{
				WAIT_W--;
				_w->Release();
			}
			else if ((NUM_W == 0) && (WAIT_W == 0) && (WAIT_R > 0))
			{
				WAIT_R--;
				_r->Release();
			}
			else
			{
				_e->Release();
			}
		}
	public:
		ReadWriteLockObject(bool isMultiThread = true) : PrintableObject(isMultiThread)
		{
			_e = new Core::Semaphore(E_SEMAPHORE_NAME, true);
			_r = new Core::Semaphore(READ_SEMAPHORE_NAME, false);
			_w = new Core::Semaphore(WRITE_SEMAPHORE_NAME, false);
		}
	};
}
