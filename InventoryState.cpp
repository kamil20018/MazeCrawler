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
                this->colOneRow = (int)this->itemTypeSelectors.size() - 1;
            }
            if (this->colOneRow >= this->itemTypeSelectors.size()) {
                this->colOneRow = 0;
            }
        }

        if (this->currColumn == 1) {
            this->colTwoRow += this->changeRowBy;
            int itemCount;
            switch ((ItemTypes)this->colOneRow) {
                case ItemTypes::SWORD:
                    itemCount = (int)this->swords.size();
                    break;
                case ItemTypes::SHIELD:
                    itemCount = (int)this->shields.size();
                    break;
                case ItemTypes::BOOTS:
                    itemCount = (int)this->boots.size();
                    break;
                default:
                    itemCount = 0;
                    break;
            }
            if (itemCount > 0) {
                if (this->colTwoRow >= itemCount) {
                    this->colTwoRow = 0;
                }
                else if (this->colTwoRow < 0) {
                    this->colTwoRow = itemCount - 1;
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
    switch ((ItemTypes)this->colOneRow) {
        case ItemTypes::SWORD:
            drawItemType(this->swords);
            break;
        case ItemTypes::SHIELD:
            drawItemType(this->shields);
            break;
        case ItemTypes::BOOTS:
            drawItemType(this->boots);
            break;
    }

    this->context->window->display();
}

template <typename T>
void InventoryState::drawItemType(std::vector<std::shared_ptr<T>> itemList) {
    int itemCount = (int)itemList.size();
    if (itemCount > 0) {
        float fieldHeight = (float)SCREEN_HEIGHT / itemCount;
        for (int i = 0; i < itemCount; i++) {
            TextField itemField(itemList[i]->getDescription(),
                                 sf::Vector2f(SCREEN_WIDTH / 3.0f, fieldHeight * i),
                                 this->context->assets->GetFont("pixel_font"), true);
            itemField.setHardBoundsSize(sf::Vector2f(SCREEN_WIDTH / 3.0f, fieldHeight));
            itemField.setBackgroundColor(colors["dark_grey"]);
            itemField.setFontColor(colors["white"]);
            itemField.setFontSize(20);

            if (i == this->colTwoRow and this->currColumn == 1) {
                itemField.setSelected(true);
            }
            this->context->window->draw(itemField);
            itemField.setSelected(false);
        }
    }
    else {
        this->context->window->draw(this->itemNotImplemented);
    }
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
            case ItemTypes::SHIELD:
                this->shields.push_back(std::dynamic_pointer_cast<Shield>(item));
                break;
            case ItemTypes::BOOTS:
                this->boots.push_back(std::dynamic_pointer_cast<Boots>(item));
                break;
        }
    }
}
