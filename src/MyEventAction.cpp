#include "MyEventAction.h"

#include <G4EventManager.hh>

MyEventAction::MyEventAction():
G4UserEventAction()
{   
}

MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event * anEvent){
}

void MyEventAction::EndOfEventAction(const G4Event * anEvent){
}


