#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <set>
#include <string>
#include <vector>

#include "appointment.hpp"

class Hospital {
public:
  Hospital() = default;
  void AddDoctor(Doctor& d);
  Doctor* GetAvailableDoctor(TimeSlot time);
  void AddAppointment(TimeSlot time, std::string patient);
  void RemoveAppointment(TimeSlot time, std::string patient);

private:
  vector<Doctor*> doctors_;
  vector<Appointment> appointments_;
};

#endif