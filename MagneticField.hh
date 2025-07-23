#ifndef MagneticField_H
#define MagneticField_H 1

#include "G4MagneticField.hh"
#include "globals.hh"
#include <CLHEP/Units/SystemOfUnits.h>

class MagneticField : public G4MagneticField 
{
public:
    MagneticField(G4double fieldValue);
    ~MagneticField() override = default;

    void GetFieldValue(const G4double point[4], double* bField) const override;

private:
    G4double fBz;
};

#endif