#include "PMActionInit.hh"

PMActionInit::PMActionInit()
{}

PMActionInit::~PMActionInit()
{}

void PMActionInit::BuildForMaster() const
{}

void PMActionInit::Build() const
{
    PMPrimaryGenerator *generator = new PMPrimaryGenerator();
    SetUserAction(generator);
}