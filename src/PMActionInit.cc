#include "PMActionInit.hh"

PMActionInit::PMActionInit()
{}

PMActionInit::~PMActionInit()
{}

void PMActionInit::BuildForMaster() const
{
    PMRunAction *runAction = new PMRunAction();
    SetUserAction(runAction);
}

void PMActionInit::Build() const
{
    PMPrimaryGenerator *generator = new PMPrimaryGenerator();
    SetUserAction(generator);

    PMRunAction *runAction = new PMRunAction();
    SetUserAction(runAction);

    PMUserSteppingAction *UserSteppingAction = new PMUserSteppingAction();
    SetUserAction(UserSteppingAction);

    PMEventAction *eventAction = new PMEventAction();
    SetUserAction(eventAction);
}