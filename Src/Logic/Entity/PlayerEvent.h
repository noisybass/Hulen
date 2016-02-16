#ifndef LOGIC_PLAYER_EVENT_H
#define LOGIC_PLAYER_EVENT_H

#include <boost/signals2/signal.hpp>

namespace Logic {

	/**
	http://www.boost.org/doc/libs/1_60_0/doc/html/signals2/tutorial.html
	*/
	class CPlayerEvent{
	public:

		typedef boost::signals2::signal <void()> signal_t;

		CPlayerEvent(){
			_instance = this;
		};

		static CPlayerEvent* getInstance(){ return _instance; }

		void addListener(const signal_t::slot_type& slot){
			_signal.connect(slot);
		}

		void fireEvent(){
			_signal();
		}

	private:
		signal_t _signal;
		static CPlayerEvent* _instance;
	};
}

#endif // LOGIC_PLAYER_EVENT_H