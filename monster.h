#ifndef _MONSTER_H
#define _MONSTER_H

#include "creature.h"
#include "shortest_path.h"
#include "enums.h"
#include "monster_ai.h"

class Monster : public Controller {
  public:
  Monster(Creature* creature, MonsterAIFactory);
  
  virtual void you(MsgType type, const string& param) const override;
  virtual void you(const string& param) const override;
  
  virtual void makeMove() override;
  virtual bool isPlayer() const;
  virtual const MapMemory& getMemory() const;

  virtual void onBump(Creature*);

  static ControllerFactory getFactory(MonsterAIFactory);

  SERIALIZATION_DECL(Monster);

  protected:
  Creature* SERIAL(creature);

  private:
  PMonsterAI SERIAL(actor);
  vector<const Creature*> SERIAL(enemies);
};

#endif
