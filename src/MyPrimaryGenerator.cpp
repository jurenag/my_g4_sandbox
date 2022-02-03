#include "MyPrimaryGenerator.h"

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4PrimaryVertex.hh>
#include <G4OpticalPhoton.hh>
#include <G4ThreeVector.hh>
#include <G4RandomDirection.hh>
#include <G4PhysicalConstants.hh>



MyPrimaryGenerator::MyPrimaryGenerator():
G4VUserPrimaryGeneratorAction(), vertex_x(0.), vertex_y(5.*cm), vertex_z(0.), kinetic_energy(10.*eV)
{
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event * anEvent)
{
    // Generate a random momentum direction for the photon

    G4double cost = 1. - 2.*G4UniformRand();
    G4double sint = std::sqrt((1.-cost)*(1.+cost));

    G4double phi = twopi*G4UniformRand();
    G4double sinp = std::sin(phi);
    G4double cosp = std::cos(phi);

    // Determine the polarization of the photon

    G4double sx = cost*cosp;
    G4double sy = cost*sinp;
    G4double sz = -sint;

    G4ThreeVector polarization(sx, sy, sz);

    G4ThreeVector momentum(0.,-1.,0.);

    G4ThreeVector perp = momentum.cross(polarization);

    phi  = twopi*G4UniformRand();
    sinp = std::sin(phi);
    cosp = std::cos(phi);

    polarization = cosp * polarization + sinp * perp;
    polarization = polarization.unit();

    G4PrimaryVertex * pVertex = new G4PrimaryVertex(vertex_x, vertex_y, vertex_z, 0.);
    G4PrimaryParticle * particle = new  G4PrimaryParticle(G4OpticalPhoton::Definition());

    particle->SetMomentumDirection(momentum);
    particle->SetPolarization(polarization);
    particle->SetKineticEnergy(kinetic_energy);

    pVertex->SetPrimary(particle);

    anEvent->AddPrimaryVertex(pVertex);
}
