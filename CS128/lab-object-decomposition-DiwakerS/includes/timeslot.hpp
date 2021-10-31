#ifndef TIMESLOT_HPP
#define TIMESLOT_HPP

struct TimeSlot {
  int startTime;
  int endTime;

  bool operator<( const TimeSlot& other ) const {
    return startTime < other.startTime;
  }

  bool operator==( const TimeSlot& other ) const {
    return startTime == other.startTime && endTime == other.endTime;
  }
};

#endif