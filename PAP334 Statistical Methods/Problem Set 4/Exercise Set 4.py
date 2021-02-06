import random
import matplotlib.pyplot as plt 
import numpy as np 

#plane seating parameters 
num_rows = 25
num_cols = 4

#simple position timing container 

class Passenger: 
    _busy_time = 0. 
    def __init__(self, seat, pos):
        self.position = pos
        self.seat = seat 
    #a printout method for debugging 
    def __repr__(self):
        return 'Passenger with seat {} at position {}' .format(self.seat, self.position)
    #is the passenger busy?
    def busy(self):
        return self._busy_time > 0.
    #pos calculation 
    def row(self):
        return int(self.seat/num_cols)
    def column(self):
        return self.seat % num_cols 
    #steppers
    def tick(self, time_step):
        self._busy_time -= time_step 
    def delay(self,delay):
        self._busy_time += delay 
    def advance(self,step):
        self.position += step 

#containers for all system parameters 
class Parameters: 
    gate_pos = -25 #distance between gate and first row in meters 
    pass_distance = 0.5 #initial distance between passengers in the queue 
    pass_speed = 0.5 #passengers move 0.5 m/s 
    seat_distance = 1. 
    delay_aisle = 30. 
    delay_swap = 15.
    time_step = 1

#boarding time generator 
def boarding_time(pars):
    #generating random seat assignment 
    num_passengers = num_rows * num_cols #assuming a 100% saturation 
    seats_attrib = random.sample(range(num_passengers), k=num_passengers)

    #passenger queue 
    boarding = [] 
    i =0
    for seat_num in seats_attrib:
        distance_from_first_row = pars.gate_pos-i*pars.pass_distance 
        boarding.append(Passenger(seat_num, distance_from_first_row))
        i +=1

    #starting boarding 
    clock = 0. 
    occupied_seats = []
    prev_passenger = boarding[0] 
    iter_dist = pars.pass_speed*pars.time_step
    while len(boarding) > 0:
        clock += pars.time_step
        for passenger in boarding: 
            if passenger.busy():
                passenger.tick(pars.time_step)
            else:
                if passenger.position == passenger.row()*pars.seat_distance:
                    #if in correct row passenger stops 
                    occupied_seats.append(passenger.seat)
                    boarding.remove(passenger)
                    continue
            if prev_passenger == boarding[0]:
                passenger.advance(iter_dist)
            if prev_passenger.position-passenger.position-iter_dist >= pars.pass_distance:
                passenger.advance(iter_dist)
            if passenger.position == passenger.row()*pars.seat_distance:
                passenger.delay(pars.delay_aisle)
                if passenger.column() == 0 and passenger.row()*num_cols+1 in occupied_seats:
                    passenger.delay(pars.delay_swap)
                if passenger.column() == 3 and passenger.row()*num_cols+1 in occupied_seats: 
                    passenger.delay(pars.delay_swap)
            
            prev_passenger = passenger
        return clock 

times = []
params = Parameters()
for i in range(100):
    times.append(boarding_time(params))
    print('generating toy {}' .format(i))

print('Mean time (s):', np.mean(times))
print('Standard deviation (s):', np.std(times))

#plots
counts, xbins, image = plt.hist(times, bins =100, label=['Boarding times'])
plt.xlabel('Boarding times /s')
plt.ylabel('Number of toys')
plt.show()