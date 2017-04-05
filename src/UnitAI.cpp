#include "UnitAI.h"

void UnitAI::Tick(float dt)
{
    for(auto command : commands)
    {
        command->tick(dt);
    }

    if(commands.front()->done())
    {
        commands.pop_front();
    }
}

void UnitAI::SetCommand(Command* c)
{
    commands.clear();
    commands.push_back(c);
}

void UnitAI::AddCommand(Command* c)
{
    commands.push_back(c);
}
