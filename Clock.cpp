 #include "Clock.h"
 Clock::Clock() { setStart(0); }
 Clock::Clock(clock_t s) {
 	setStart(s);
 }
 void Clock::start() {
 	setStart(clock());
 }
 void Clock::setStart(clock_t ts) {
 	start_ts = (ts>0)?ts:clock();
 }
 clock_t Clock::getStart() {
 	return start_ts;
 }
 double Clock::getElapsedTime() {
 	return static_cast<double>(clock()-getStart()) / CLOCKS_PER_SEC ;
 }

