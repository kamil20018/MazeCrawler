#include "InventoryState.h"

InventoryState::InventoryState(std::shared_ptr<Context>& context){
    this->context = context;
    this->currColumn = 0;
    this->colOneRow = 0;
    this->colTwoRow = 0;
    this->implementedItems.push_back(ItemTypes::SWORD);
}

InventoryState::~InventoryState() {

}

void InventoryState::Init() {
    //Item not implemented yet init
    std::string txt = "this item type \nisn't implemented";
    TextField notImpl(txt, sf::Vector2f(SCREEN_WIDTH / 3.0f, 0), 
                      this->context->assets->GetFont("pixel_font"), true);
    notImpl.setHardBoundsSize(sf::Vector2f(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT));
    notImpl.setBackgroundColor(colors["red"]);
    notImpl.setFontColor(colors["green"]);
    this->itemNotImplemented = notImpl;

    //left site init
    float selectorHeight = SCREEN_HEIGHT / (float)((int)ItemTypes::LAST_ELEMENT);
    float selectorWidth = SCREEN_WIDTH / 3.0f;
    for (int i = 0; i < (int)ItemTypes::LAST_ELEMENT; i++) {
        std::string name = itemEnumToString((ItemTypes)i) + "s";
        std::cout << name << std::endl;
        TextField itemTypeSelector(name, sf::Vector2f(0.0f, selectorHeight * i),
                                   this->context->assets->GetFont("pixel_font"), true);
        itemTypeSelector.setBackgroundColor(colors["dark_grey"]);
        itemTypeSelector.setFontColor(colors["white"]);
        itemTypeSelector.setHardBoundsSize(sf::Vector2f(selectorWidth, selectorHeight));
        this->itemTypeSelectors.push_back(itemTypeSelector);
    }
}

void InventoryState::ProcessInput() {
    sf::Event event;
    while (this->context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                this->context->states->PopCurrent();
                break;
            case sf::Keyboard::C:
                for (auto item : this->items) {
                    item->print();
                }
                break;
            case sf::Keyboard::W:
                this->changeRowBy = -1;
                break;
            case sf::Keyboard::S:
                this->changeRowBy = 1;
                break;
            case sf::Keyboard::A:
                this->changeColBy = -1;
                break;
            case sf::Keyboard::D:
                this->changeColBy = 1;
                break;
            }

        }
    }
}

void InventoryState::Update() {
    if (this->changeRowBy != 0) {
        if (this->currColumn == 0) {
            this->colOneRow += this->changeRowBy;
            if (this->colOneRow < 0) {
                this->colOneRow = this->itemTypeSelectors.size() - 1;
            }
            if (this->colOneRow >= this->itemTypeSelectors.size()) {
                this->colOneRow = 0;
            }
        }

        if (this->currColumn == 1) {
            this->colTwoRow += this->changeRowBy;
            if ((ItemTypes)this->colOneRow == ItemTypes::SWORD) {
                if (this->colTwoRow >= (int)this->swords.size()) {
                    this->colTwoRow = 0;
                }
                else if (this->colTwoRow < 0) {
                    this->colTwoRow = this->swords.size() - 1;
                }
            }
            else {
                
                this->colTwoRow = 0;
            }
        }

        this->changeRowBy = 0;
    }
    if (this->changeColBy != 0) {
        this->currColumn += this->changeColBy;
        if (this->currColumn >= this->columnCount) {
            this->currColumn = 0;
        }

        if (this->currColumn < 0) {
            this->currColumn = this->columnCount - 1;
        }
        this->changeColBy = 0;
    }

}

void InventoryState::Draw() {
    this->context->window->clear(colors["green"]);
    for (int i = 0; i < this->itemTypeSelectors.size(); i++) {
        if (this->colOneRow == i) {
            this->itemTypeSelectors[i].setSelected(true);
            this->context->window->draw(this->itemTypeSelectors[i]);
            this->itemTypeSelectors[i].setSelected(false);
        }
        else {
            this->context->window->draw(this->itemTypeSelectors[i]);
        }
    }

    if ((ItemTypes)this->colOneRow == ItemTypes::SWORD) {
        int swordCount = this->swords.size();
        if (swordCount > 0) {
            float fieldHeight = SCREEN_HEIGHT / swordCount;
            for (int i = 0; i < swordCount; i++) {
                TextField swordField(this->swords[i]->getDescription(),
                                     sf::Vector2f(SCREEN_WIDTH / 3.0f, fieldHeight * i),
                                     this->context->assets->GetFont("pixel_font"), true);
                swordField.setHardBoundsSize(sf::Vector2f(SCREEN_WIDTH / 3.0f, fieldHeight));
                swordField.setBackgroundColor(colors["dark_grey"]);
                swordField.setFontColor(colors["white"]);
                swordField.setFontSize(20);

                if (i == this->colTwoRow and this->currColumn == 1) {
                    swordField.setSelected(true);
                }
                this->context->window->draw(swordField);
                swordField.setSelected(false);
            }
        }
    }
    else {
        this->context->window->draw(this->itemNotImplemented);
    }

    this->context->window->display();
}

States InventoryState::getState() {
    return States::INVENTORY;
}

void InventoryState::AddItems(std::vector<std::shared_ptr<Item>> newItems){
    this->items.insert(this->items.end(), newItems.begin(), newItems.end());
    for (std::shared_ptr<Item> item : newItems) {
        switch (item->getType()) {
            case ItemTypes::SWORD:
                this->swords.push_back(std::dynamic_pointer_cast<Sword>(item));
                break;
            case ItemTypes::BOOTS:
                break;
        }
    }
}

