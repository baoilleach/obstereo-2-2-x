#include <boost/test/minimal.hpp>
#include <cassert>

#include <iostream>

#include <openbabel/mol.h>

using namespace std;
using namespace OpenBabel;

unsigned long GetId(OBAtom *atom)
{
  OBPairTemplate<unsigned long> *data = dynamic_cast<OBPairTemplate<unsigned long>*>(atom->GetData("id"));
  if (!data)
    return -1;
  return data->GetGenericValue();
}

OBAtom* GetAtomById(OBMol *mol, unsigned long id)
{
  FOR_ATOMS_OF_MOL (atom, mol) {
    if (GetId(&*atom) == id)
      return &*atom;
  }

  return 0;
}

// OBMol::NewAtom()
void testIdsNewAtom()
{
  OBMol mol;
  for (int i = 0; i < 10; ++i) {
    OBAtom *atom = mol.NewAtom();
    cout << GetId(atom) << endl;
    BOOST_REQUIRE(GetId(atom) == i);
  }

  BOOST_REQUIRE( GetAtomById(&mol, 0) );
  BOOST_REQUIRE( GetAtomById(&mol, 4) );
  BOOST_REQUIRE( GetAtomById(&mol, 9) );
  BOOST_REQUIRE( !GetAtomById(&mol, 10) );
  
  BOOST_REQUIRE( GetAtomById(&mol, 0)->GetIdx() == 1 );
  BOOST_REQUIRE( GetAtomById(&mol, 4)->GetIdx() == 5 );
  BOOST_REQUIRE( GetAtomById(&mol, 9)->GetIdx() == 10 );
}

void testIdsDeleteAtom()
{
  OBMol mol;
  for (int i = 0; i < 10; ++i)
    mol.NewAtom();

  BOOST_REQUIRE( GetAtomById(&mol, 3) );
  BOOST_REQUIRE( GetAtomById(&mol, 4) );
  BOOST_REQUIRE( GetAtomById(&mol, 5) );

  mol.DeleteAtom(GetAtomById(&mol, 4));

  BOOST_REQUIRE( GetAtomById(&mol, 3) );
  BOOST_REQUIRE( GetAtomById(&mol, 3)->GetIdx() == 4 );
  BOOST_REQUIRE( !GetAtomById(&mol, 4) );
  BOOST_REQUIRE( GetAtomById(&mol, 5) );
  BOOST_REQUIRE( GetAtomById(&mol, 5)->GetIdx() == 5 );
}

void testIdsAddAtom()
{
  OBMol mol;
  // add 5 atoms
  for (int i = 0; i < 5; ++i)
    mol.NewAtom();

  OBAtom a;
  a.SetAtomicNum(6);
  // add a sixth atom
  mol.AddAtom(a);

  BOOST_REQUIRE( mol.NumAtoms() == 6 );
  BOOST_REQUIRE( GetAtomById(&mol, 5) );
  BOOST_REQUIRE( GetAtomById(&mol, 5)->GetIdx() == 6 );
}

int test_main(int,char**) 
{
  testIdsNewAtom();
  testIdsDeleteAtom();
  testIdsAddAtom();
  
  return 0;
}

                
