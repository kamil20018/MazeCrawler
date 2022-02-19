#include "GamePlay.h"


GamePlay::GamePlay(std::shared_ptr<Context>& context) : context(context), state(Turn::HERO_TURN) {
    this->middlePos = 0.0f; //initialization just to get rid of a warning
    srand((unsigned int)time(NULL));
}

GamePlay::~GamePlay(){

}

void GamePlay::Init(){

    this->context->assets->AddTexture("goblin", "Resources/Textures/Goblin.png");
    this->context->assets->AddTexture("hero", "Resources/Textures/Hero.png");

    this->enemyManager = std::make_shared<EnemyManager>();
    this->hero = std::make_shared<Hero>(sf::Vector2i(1, 1), this->context->assets->GetTexture("hero"));
    this->floor = std::make_shared<Floor>(10, 12, hero, enemyManager);

    std::shared_ptr<Goblin> goblin1 = std::make_shared<Goblin>(sf::Vector2i(1, 1), this->floor);
    std::shared_ptr<Goblin> goblin2 = std::make_shared<Goblin>(sf::Vector2i(1, 2), this->floor);
    std::shared_ptr<Goblin> goblin3 = std::make_shared<Goblin>(sf::Vector2i(2, 1), this->floor);
    goblin1->addTexture(context->assets->GetTexture("goblin"));
    goblin2->addTexture(context->assets->GetTexture("goblin"));
    goblin3->addTexture(context->assets->GetTexture("goblin"));

    std::vector<std::shared_ptr<Enemy>> enemyList = { goblin1, goblin2, goblin3 };


    this->heroStatus = std::make_shared<HeroStatus>(hero->getHeroData(), context->assets->GetFont("pixel_font"));
    this->enemyManager->setEnemyList(enemyList);

    this->attackListener = std::make_shared<AttackListener>(this->hero, this->enemyManager);
    this->hero->setAttackListener(this->attackListener);
    this->enemyManager->setAttackListener(this->attackListener);

    this->middlePos = (float)(this->WINDOW_HEIGHT - 75) / 2;
}

void GamePlay::ProcessInput(){
    sf::Event event;
    while (this->context->window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            this->context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                this->moveDir = dir::up;
                break;
            case sf::Keyboard::S:
                this->moveDir = dir::down;
                break;
            case sf::Keyboard::A:
                this->moveDir = dir::left;
                break;
            case sf::Keyboard::D:
                this->moveDir = dir::right;
                break;
            case sf::Keyboard::M:
                this->itemManagerOpen = true;
                break;
            case sf::Keyboard::I:
                this->context->states->ToInventoryState();
                break;
            case sf::Keyboard::C: //debug for stored items
                for (std::shared_ptr<Item> item : this->items) {
                    item->print();
                }
                break;
            case sf::Keyboard::F:
                this->context->states->AddState(std::make_shared<GamePlay>(this->context));
                break;
            case sf::Keyboard::G:
                this->context->states->SwapPrevious();
                break;
            case sf::Keyboard::Space:
                this->state = Turn::ENEMY_TURN;
                break;
            default:
                break;
            }
        }
    }
}

void GamePlay::Update(){
    if (this->itemManagerOpen) {
        this->itemManagerOpen = false;
        this->context->states->AddState(std::make_unique<ItemChooseState>(this->context, this->items));
        this->items.clear();
    }


    sf::Vector2i heroPos = this->hero->getPosition();
    bool canMoveByDir = this->floor->canMoveTo(heroPos, this->moveDir);
    switch(this->state) {
    case Turn::HERO_TURN:

        if (not this->hero->canTakeAction() and utils::isNonZero(this->moveDir)) {
            std::cout << "insufficient energy to perform any action, enemy turn" << std::endl;
            this->state = Turn::ENEMY_TURN;
            this->moveDir = sf::Vector2i(0, 0);
        }
        else if (canMoveByDir and utils::isNonZero(this->moveDir)) {
            if (this->hero->canMove()) {
                this->hero->move(this->moveDir);
            }
            this->enemyManager->updatePathToHero();
            this->moveDir = sf::Vector2i(0, 0);
        }
        else if (not canMoveByDir and this->enemyManager->isEnemyAt(heroPos + this->moveDir) and this->floor->isPathTo(heroPos, this->moveDir) and utils::isNonZero(this->moveDir)) {
            utils::printVector("attacked an enemy at: ", heroPos + this->moveDir);
            this->hero->meeleAttack(heroPos + this->moveDir);

            EnemyLoot loot = this->enemyManager->getLootFromDead();
            this->items.insert(items.end(), loot.items.begin(), loot.items.end());
            this->hero->getLoot(loot);


            this->enemyManager->removeDead();
            this->moveDir = sf::Vector2i(0, 0);
        }
        break;

    case Turn::ENEMY_TURN:
        this->enemyManager->takeTurn();
        this->state = Turn::HERO_TURN;
        this->hero->turnPassed();
        break;
    }
}

void GamePlay::Draw(){
    sf::Vector2i heroPos = this->hero->getPosition();
    this->context->window->clear(colors["red"]);
    true;

    sf::Texture floorTexture = floor->getTexture();

    sf::Sprite mazeSprite;
    mazeSprite.setTexture(floorTexture);
    mazeSprite.setPosition(middlePos, middlePos);
    mazeSprite.move(-heroPos.x * 75.0f, -heroPos.y * 75.0f);

    sf::Sprite heroSprite;
    heroSprite.setTexture(hero->getTexture());
    heroSprite.setPosition(middlePos, middlePos);
        

    this->context->window->draw(mazeSprite);
    this->context->window->draw(heroSprite);
    for (std::shared_ptr enemy : this->enemyManager->getEnemyList()) {
        this->context->window->draw(*enemy);
    }
    this->context->window->draw(*heroStatus);
        
    this->context->window->display();
}

void GamePlay::Pause(){
    isPaused = true;
}

void GamePlay::Start(){
    isPaused = false;
}

States GamePlay::getState() {
    return States::GAMEPLAY;
}