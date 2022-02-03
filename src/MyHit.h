#include <G4VHit.hh>
#include <G4ThreeVector.hh>
#include <G4THitsCollection.hh>

class MyHit : public G4VHit{
    public:
        MyHit();
        MyHit(const MyHit&);
        ~MyHit();

        MyHit& operator=(const MyHit&);
        G4bool operator==(const MyHit&) const;

        void* operator new(size_t);
        void  operator delete(void*);

        void Print() override;

        // Set methods
        void SetSensorID (G4int input)                      {sensor_id = input;}
        void SetInitHitPos(G4ThreeVector  input)            {init_hit_pos = input;}

        // Get methods
        G4int GetSensorId() const                 {return sensor_id;}
        G4ThreeVector   GetInitHitPos() const     {return init_hit_pos;}

    private:
        G4int                   sensor_id;
        G4ThreeVector           init_hit_pos;
};

extern G4Allocator<MyHit> MyHitAllocator;

inline void* MyHit::operator new(size_t)
{return ((void*) MyHitAllocator.MallocSingle());}

inline void MyHit::operator delete(void* hit)
{MyHitAllocator.FreeSingle((MyHit*) hit);}

