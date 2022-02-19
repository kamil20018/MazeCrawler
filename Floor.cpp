#include "Floor.h"

Floor::Floor(int width, int height, std::shared_ptr<Hero> hero, std::shared_ptr<EnemyManager> enemyManager) {
	this->width = width;
	this->height = height;
    this->hero = hero;
    this->enemyManager = enemyManager;

	std::vector<std::vector<bool>> hozWalls(height, std::vector<bool>(width + 1, true));
	std::vector<std::vector<bool>> vertWalls(height + 1, std::vector<bool>(width, true));
    std::vector<std::vector<bool>> seenCells(height, std::vector<bool>(width, false));

	this->horizontalWalls = hozWalls;
	this->verticalWalls = vertWalls;
    this->seenCells = seenCells;

    this->entrance = sf::Vector2i(rand() % (width / 5), rand() % (height / 5));
    this->exit = sf::Vector2i(width * 4 / 5 + rand() % (width / 5), height * 4 / 5 + rand() % (height / 5));

    this->hero->setPosition(this->entrance);
    //generateMazeAlt();
    generateMazeWilson();
}

void Floor::generateMazeDfs(sf::Vector2i entrance) {

    std::vector<std::vector<bool>> maze(height, std::vector<bool>(width, false));
    std::vector<sf::Vector2i> stack;
    maze[entrance.y][entrance.x] = true;
    stack.push_back(entrance);

    while (!stack.empty()) {
        sf::Vector2i currCell = stack.back();
        std::vector<sf::Vector2i> possibleDirections;
        for (sf::Vector2i dir : dirs) {
            sf::Vector2i testPos = currCell + dir;
            if (vectorInBounds(testPos) and not maze[testPos.y][testPos.x]) {
                possibleDirections.push_back(testPos);
            }
        }
        if (possibleDirections.empty()) {
            stack.pop_back();
        }
        else {
            sf::Vector2i nextCell = possibleDirections[rand() % possibleDirections.size()];
            stack.push_back(nextCell);
            maze[nextCell.y][nextCell.x] = true;
            sf::Vector2i dir = nextCell - currCell;
            if (dir.x != 0) {
                if (dir.x == -1) {
                    horizontalWalls[currCell.y][currCell.x] = false;
                }
                else if (dir.x == 1) {
                    horizontalWalls[currCell.y][currCell.x + 1] = false;
                }
            }
            else {
                if (dir.y == -1) {
                    verticalWalls[currCell.y][currCell.x] = false;
                }
                else if (dir.y == 1) {
                    verticalWalls[currCell.y + 1][currCell.x] = false;
                }
            }
        }
    }
}

void Floor::generateMazeAlt() {
    std::vector<std::vector<bool>> maze(height, std::vector<bool>(width, false));
    std::vector<sf::Vector2i> stack;
    maze[0][0] = true;
    sf::Vector2i currCell = sf::Vector2i(0, 0);
    while (not allVisited(maze)) {
        utils::printVector(currCell);
        std::vector<sf::Vector2i> possibleDirections;
        for (sf::Vector2i dir : dirs) {
            sf::Vector2i testPos = currCell + dir;
            utils::printVector("testPos: ", testPos);
            if (vectorInBounds(testPos) and not maze[testPos.y][testPos.x]) {
                possibleDirections.push_back(testPos);
            }
        }
        if (possibleDirections.empty()) {
            bool found = false;
            for (int j = 0; j < this->height; j++) {
                if (found) {
                    found = false;
                    break;
                }
                for (int i = 0; i < this->width; i++) {
                    if (not maze[j][i]) {
                        currCell = sf::Vector2i(i, j);
                        maze[j][i] = true;
                        std::vector<sf::Vector2i> visitedDirs;
                        for (sf::Vector2i dir : dirs) {
                            sf::Vector2i testPos = currCell + dir;
                            if (vectorInBounds(testPos) and maze[testPos.y][testPos.x]) {
                                visitedDirs.push_back(dir);
                                utils::printVector("visited dir", dir);
                            }
                        }
                        sf::Vector2i dir = visitedDirs[rand() % visitedDirs.size()];
                        if (dir.x != 0) {
                            if (dir.x == -1) {
                                horizontalWalls[currCell.y][currCell.x] = false;
                            }
                            else if (dir.x == 1) {
                                horizontalWalls[currCell.y][currCell.x + 1] = false;
                            }
                        }
                        else {
                            if (dir.y == -1) {
                                verticalWalls[currCell.y][currCell.x] = false;
                            }
                            else if (dir.y == 1) {
                                verticalWalls[currCell.y + 1][currCell.x] = false;
                            }
                        }
                        found = true;
                        break;
                    }
                }
            }
        }
        else {
            sf::Vector2i nextCell = possibleDirections[rand() % possibleDirections.size()];
            maze[nextCell.y][nextCell.x] = true;
            sf::Vector2i dir = nextCell - currCell;
            if (dir.x != 0) {
                if (dir.x == -1) {
                    horizontalWalls[currCell.y][currCell.x] = false;
                }
                else if (dir.x == 1) {
                    horizontalWalls[currCell.y][currCell.x + 1] = false;
                }
            }
            else {
                if (dir.y == -1) {
                    verticalWalls[currCell.y][currCell.x] = false;
                }
                else if (dir.y == 1) {
                    verticalWalls[currCell.y + 1][currCell.x] = false;
                }
            }
            currCell = nextCell;
        }
        
    }
}

void Floor::generateMazeWilson() {
    std::vector<std::vector<bool>> maze(height, std::vector<bool>(width, false));
    maze[height - 1][width - 1] = true;
    sf::Vector2i currCell = sf::Vector2i(0, 0);
    std::vector<sf::Vector2i> path = { currCell };
    while (not allVisited(maze)) {

        bool pathConnected = false;
        while (not pathConnected) {
            utils::printVector("currCell: ", currCell);
            std::vector<sf::Vector2i> possibleDirs;
            for (sf::Vector2i dir : dirs) {
                if (vectorInBounds(currCell + dir)) {
                    if (path.size() > 1 and (path[path.size() - 2] != currCell + dir)) {
                        possibleDirs.push_back(dir);
                    }
                    else if (path.size() == 1) {
                        possibleDirs.push_back(dir);
                    }
                }
            }
            sf::Vector2i nextCell = currCell + possibleDirs[rand() % possibleDirs.size()];
            //check if next cell is a part of path - we have to remove the resulting loop
            std::optional<int> index;
            for (int i = 0; i < path.size(); i++) {
                if (path[i] == nextCell) {
                    index.emplace(i);
                    break;
                }
            }
            if (index.has_value()) {
                for (int i = path.size() - 1; i > index.value(); i--) {
                    utils::printVector("erased: ", path[i]);
                    path.erase(path.begin() + i);
                }
                currCell = path.back();
                for (sf::Vector2i pos : path) {
                    utils::printVector(pos);
                }
            }
            else if (maze[currCell.y][currCell.x]) {
                pathConnected = true;
            }
            else {
                path.push_back(nextCell);
                currCell = nextCell;
            }
        }
        for (sf::Vector2i cell : path) {
            maze[cell.y][cell.x] = true;
        }
        for (int i = 0; i < path.size() - 1; i++) {
            sf::Vector2i pathCell = path[i];
            sf::Vector2i dir = path[i + 1] - path[i];
            if (dir.x != 0) {
                if (dir.x == -1) {
                    horizontalWalls[pathCell.y][pathCell.x] = false;
                }
                else if (dir.x == 1) {
                    horizontalWalls[pathCell.y][pathCell.x + 1] = false;
                }
            }
            else {
                if (dir.y == -1) {
                    verticalWalls[pathCell.y][pathCell.x] = false;
                }
                else if (dir.y == 1) {
                    verticalWalls[pathCell.y + 1][pathCell.x] = false;
                }
            }
        }
        path.clear();
        bool breakOut = false;
        for (int x = 0; x < this->width; x++) {
            if (breakOut) {
                break;
            }
            for (int y = 0; y < this->height; y++) {
                if (not maze[y][x]) {
                    currCell = sf::Vector2i(x, y);
                    path.push_back(currCell);
                    breakOut = true;
                    break;
                }
            }
        }
    }
}

bool Floor::allVisited(std::vector<std::vector<bool>> maze) {
    for (std::vector<bool> row : maze) {
        for (bool isCellVisited : row) {
            if (not isCellVisited) {
                return false;
            }
        }
    }
    return true;
}

bool Floor::vectorInBounds(sf::Vector2i pos) {
    return pos.x >= 0 and pos.y >= 0 and pos.x < this->width and pos.y < this->height;
}

const sf::Texture& Floor::getTexture() {

    float CELL_SIZE = 75.0f;
    float WALL_SIZE = 5.0f;
    float OFFSET = 30.0f;

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape wallHoz(sf::Vector2f(WALL_SIZE, CELL_SIZE + 4));
    sf::RectangleShape wallVer(sf::Vector2f(CELL_SIZE + 4, WALL_SIZE));
    wallHoz.setFillColor(sf::Color::Black);
    wallVer.setFillColor(sf::Color::Black);
    this->renderTexture.create((unsigned int)(this->width * CELL_SIZE), 
                               (unsigned int)(this->height * CELL_SIZE));

    sf::RectangleShape visibleCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    visibleCell.setFillColor(sf::Color::Blue);

    sf::Vector2i heroPos = this->hero->getPosition();
    std::vector<sf::Vector2i> visibleCells;
    getVisibleNeighbours(0, heroPos, heroPos, visibleCells);
    for (sf::Vector2i visCell : visibleCells) {
        this->seenCells[visCell.y][visCell.x] = true;
    }
    sf::Color grey = sf::Color(105, 105, 105);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            cell.setPosition(sf::Vector2f(CELL_SIZE * x, CELL_SIZE * y));
            if (entrance.x == x and entrance.y == y) {
                cell.setFillColor(sf::Color::Green);
            }
            else if (exit.x == x and exit.y == y) {
                cell.setFillColor(sf::Color::Blue);
            }
            else if (this->seenCells[y][x]) {
                cell.setFillColor(sf::Color(55, 55, 55));
            }
            else {
                //cell.setFillColor(sf::Color(5, 5, 5));
                cell.setFillColor(sf::Color::Black);
            }
            this->renderTexture.draw(cell);
            cell.setFillColor(sf::Color::White);
        }
    }

    for (sf::Vector2i visibleCell : visibleCells) {
        cell.setPosition(sf::Vector2f(CELL_SIZE * visibleCell.x, CELL_SIZE * visibleCell.y));
        this->renderTexture.draw(cell);
    }



    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width + 1; x++) {
            if (horizontalWalls[y][x] == true) {
                wallHoz.setPosition(CELL_SIZE * x, CELL_SIZE * y);
                this->renderTexture.draw(wallHoz);
            }
        }
    }

    for (int y = 0; y < height + 1; y++) {
        for (int x = 0; x < width; x++) {
            if (verticalWalls[y][x] == true) {
                wallVer.setPosition(CELL_SIZE * x, CELL_SIZE * y);
                this->renderTexture.draw(wallVer);
            }
        }
    }

    this->renderTexture.display();
    return this->renderTexture.getTexture();
}

void Floor::getVisibleNeighbours(int depth, sf::Vector2i previousCell, sf::Vector2i currentCell, std::vector<sf::Vector2i>& visibleNeighbours) {

    visibleNeighbours.push_back(currentCell);
    if (depth == this->hero->getVision()) {
        return;
    }
    for (sf::Vector2i dir : dirs) {
        if (isPathTo(currentCell, dir) and currentCell + dir != previousCell) {
            getVisibleNeighbours(depth + 1, currentCell, currentCell + dir, visibleNeighbours);
        }
    }

}

bool Floor::canMoveTo(sf::Vector2i startPos, sf::Vector2i dir) {
    if (not isPathTo(startPos, dir)) return false;
    sf::Vector2i destination = startPos + dir;
    std::vector<sf::Vector2i> enemyPositions = enemyManager->getEnemyPositions();
    if (utils::isInVector(destination, enemyPositions) or destination == hero->getPosition() or not vectorInBounds(destination)) {
        return false;
    }
    return true;
}

bool Floor::isPathTo(sf::Vector2i startPos, sf::Vector2i dir) { // dir is supposed to be a unit vector
    sf::Vector2i destination = startPos + dir;
    if (not vectorInBounds(destination)) return false;
    if (dir.x != 0) {
        if (dir.x == -1) {
            return not horizontalWalls[startPos.y][startPos.x];
        }
        else if (dir.x == 1) {
            return not horizontalWalls[startPos.y][startPos.x + 1];
        }
    }
    else {
        if (dir.y == -1) {
            return not verticalWalls[startPos.y][startPos.x];
        }
        else if (dir.y == 1) {
            return not verticalWalls[startPos.y + 1][startPos.x];
        }
    }
    return false; 
}

sf::Vector2i Floor::getHeroPos() {
    return this->hero->getPosition();
}

std::vector<sf::Vector2i> Floor::getPath(sf::Vector2i start, sf::Vector2i end) {
    std::vector<std::vector<bool>> visitedCells(height, std::vector<bool>(width, false));
    std::vector<sf::Vector2i> path{ start };
    sf::Vector2i currentCell = start;
    visitedCells[currentCell.y][currentCell.x] = true;
    while (currentCell != end) {
        std::vector<sf::Vector2i> possibleDirections;
        for (sf::Vector2i dir : dirs) {
            sf::Vector2i testPos = currentCell + dir;
            if (vectorInBounds(testPos) and isPathTo(currentCell, dir) and not visitedCells[testPos.y][testPos.x]) {
                possibleDirections.push_back(testPos);
            }
        }

        if (possibleDirections.empty()) {
            path.pop_back();
            currentCell = path.back();
        }
        else {
            currentCell = possibleDirections[rand() % possibleDirections.size()];
            visitedCells[currentCell.y][currentCell.x] = true;
            path.push_back(currentCell);

        }
    }
    return path;
}