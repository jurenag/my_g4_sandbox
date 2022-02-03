#include "MyHit.h"

#include <G4Allocator.hh>

G4Allocator<MyHit> MyHitAllocator;

MyHit::MyHit(): 
G4VHit(), sensor_id(-1), init_hit_pos()
{
}

MyHit::MyHit(const MyHit& other): 
G4VHit()
{
    *this = other;
}

MyHit::~MyHit()
{
}

MyHit& MyHit::operator=(const MyHit& other){
    sensor_id = other.sensor_id;
    init_hit_pos = other.init_hit_pos;
    return *this;
}

G4bool MyHit::operator==(const MyHit& other) const{
    return this==&other?true:false;
}

void MyHit::Print(){
    G4cout << "sensor_id=" << this->GetSensorId() << G4endl;
    G4cout << "init_hit_pos=" << "(" << this->GetInitHitPos().getX() << ", " << this->GetInitHitPos().getY() << ", " << this->GetInitHitPos().getZ() << ")" << G4endl;
}

