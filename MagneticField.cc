
#include "MagneticField.hh"

MagneticField::MagneticField(G4double fieldValue) : fBz(fieldValue)
{}

void MagneticField::GetFieldValue(const G4double[4], double* bField) const
{
    bField[0] = 0.0; // Bx
    bField[1] = 0.0; // By  
    bField[2] = fBz; // Bz
}