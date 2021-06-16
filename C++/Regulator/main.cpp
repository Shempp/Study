#include <vector>
#include <memory>
#include <ctime>

#include "Car.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

namespace {
    std::vector<std::unique_ptr<sCar>> cars;
    std::vector<eDirection> queueСarsToSpawn;
    const auto numOfCarTypes = 3;

    // Задают представление ширины и высоты прямоугольника машины, направленного влево/вправо (sRect)
    const auto defaultCarWidth = 200;
    const auto defaultCarHeight = 100;

    // +1/-1: машины с противоположным направлением движения не должны пересекаться
    // для top/bot машин sRect перевернут соответственно
    const auto pixelFromMainAxis = 1;
    const auto startRectForTopCar = sRect(SCREEN_WIDTH / 2 - defaultCarHeight - pixelFromMainAxis, 
                                            0, 
                                            defaultCarHeight, 
                                            defaultCarWidth);
    const auto startRectForBotCar = sRect(SCREEN_WIDTH / 2 + pixelFromMainAxis, 
                                            SCREEN_HEIGHT - defaultCarWidth,
                                            defaultCarHeight, 
                                            defaultCarWidth);
    const auto startRectForLeftCar = sRect(0, 
                                            SCREEN_HEIGHT / 2 + pixelFromMainAxis, 
                                            defaultCarWidth, 
                                            defaultCarHeight);
    const auto startRectForRightCar = sRect(SCREEN_WIDTH - defaultCarWidth, 
                                            SCREEN_HEIGHT / 2 - defaultCarHeight - pixelFromMainAxis, 
                                            defaultCarWidth, 
                                            defaultCarHeight);

    const auto defaultFuel = 100;
    const auto defaultSpeed = 1;
}

// Функция проверяет, пересекает ли заданный прямоугольник прямоугольник перекрестка
inline bool isCrossIntersection(const sRect& rect)
{
    static const auto intersectionRect = sRect(SCREEN_WIDTH / 2 - defaultCarHeight - pixelFromMainAxis,
                                                SCREEN_HEIGHT / 2 - defaultCarHeight - pixelFromMainAxis,
                                                (defaultCarHeight + pixelFromMainAxis) * 2,
                                                (defaultCarHeight + pixelFromMainAxis) * 2);

    return rect.intersects(intersectionRect);
}

// Функция проверят, возможно ли создание новой машины на начальных координатах (т.е. если там нет другой машины)
bool canSpawnCarFromStartRect(eDirection dir)
{
    const sRect* rect = nullptr;
    switch(dir) {
    case eDirection::UP:
        rect = &startRectForBotCar;
        break;
    case eDirection::DOWN:
        rect = &startRectForTopCar;
        break;
    case eDirection::RIGHT:
        rect = &startRectForLeftCar;
        break;
    case eDirection::LEFT:
        rect = &startRectForRightCar;
        break;
    }

    if (!rect) {
        return false;
    }

    for (const auto& car : cars) {
        if (car->m_dir == dir) {
            if (car->m_rect.intersects(*rect)) {
                return false;
            }
        }
    }

    return true;
}

void spawnCarFromTop() 
{
    sCar* car = nullptr;
    auto dir = eDirection::DOWN;

    auto rndTypeCar = rand() % numOfCarTypes;
    if (rndTypeCar == 0) {
        car = new sGasEngine(startRectForTopCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 1) {
        car = new sElectroCar(startRectForTopCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 2) {
        car = new sHybrid(startRectForTopCar, dir, defaultSpeed, defaultFuel / 2, defaultFuel / 2);
    }

    if (!car) {
        return;
    }

    cars.push_back(std::unique_ptr<sCar>(car));
}

void spawnCarFromBot() 
{
    sCar* car = nullptr;
    auto dir = eDirection::UP;

    auto rndTypeCar = rand() % numOfCarTypes;
    if (rndTypeCar == 0) {
        car = new sGasEngine(startRectForBotCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 1) {
        car = new sElectroCar(startRectForBotCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 2) {
        car = new sHybrid(startRectForBotCar, dir, defaultSpeed, defaultFuel / 2, defaultFuel / 2);
    }

    if (!car) {
        return;
    }

    cars.push_back(std::unique_ptr<sCar>(car));
}

void spawnCarFromLeft() 
{
    sCar* car = nullptr;
    auto dir = eDirection::RIGHT;

    auto rndTypeCar = rand() % numOfCarTypes;
    if (rndTypeCar == 0) {
        car = new sGasEngine(startRectForLeftCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 1) {
        car = new sElectroCar(startRectForLeftCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 2) {
        car = new sHybrid(startRectForLeftCar, dir, defaultSpeed, defaultFuel / 2, defaultFuel / 2);
    }

    if (!car) {
        return;
    }

    cars.push_back(std::unique_ptr<sCar>(car));
}

void spawnCarFromRight() 
{
    sCar* car = nullptr;
    auto dir = eDirection::LEFT;

    auto rndTypeCar = rand() % numOfCarTypes;
    if (rndTypeCar == 0) {
        car = new sGasEngine(startRectForRightCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 1) {
        car = new sElectroCar(startRectForRightCar, dir, defaultSpeed, defaultFuel);
    }
    else if (rndTypeCar == 2) {
        car = new sHybrid(startRectForRightCar, dir, defaultSpeed, defaultFuel / 2, defaultFuel / 2);
    }

    if (!car) {
        return;
    }

    cars.push_back(std::unique_ptr<sCar>(car));
}

// Функция производит попытку создания новых машин, процесс которого пришлось отложить, т.к. там была другая машина
void trySpawnCarFromQueue()
{
    for (auto it = queueСarsToSpawn.begin(); it != queueСarsToSpawn.end();) {
        auto dir = *it;
        if (canSpawnCarFromStartRect(*it)) {
            switch (dir) {
            case eDirection::UP:
                spawnCarFromBot();
                break;
            case eDirection::DOWN:
                spawnCarFromTop();
                break;
            case eDirection::RIGHT:
                spawnCarFromLeft();
                break;
            case eDirection::LEFT:
                spawnCarFromRight();
                break;
            }

            it = queueСarsToSpawn.erase(it);
        }
        else {
            ++it;
        }
    }
}

void spawnCar()
{
    static const auto numOfSides = sizeof(eDirection);
    auto rndSide = rand() % numOfSides;
    if (rndSide == 0) {
        if (canSpawnCarFromStartRect(eDirection::LEFT)) {
            spawnCarFromRight();
        }
        else {
            queueСarsToSpawn.push_back(eDirection::LEFT);
        }
    }
    else if (rndSide == 1) {
        if (canSpawnCarFromStartRect(eDirection::DOWN)) {
            spawnCarFromTop();
        }
        else {
            queueСarsToSpawn.push_back(eDirection::DOWN);
        }
    }
    else if (rndSide == 2) {
        if (canSpawnCarFromStartRect(eDirection::UP)) {
            spawnCarFromBot();
        }
        else {
            queueСarsToSpawn.push_back(eDirection::UP);
        }
    }
    else if (rndSide == 3) {
        if (canSpawnCarFromStartRect(eDirection::RIGHT)) {
            spawnCarFromLeft();
        }
        else {
            queueСarsToSpawn.push_back(eDirection::RIGHT);
        }
    }
}

void checkMoveCarsFromAllSides()
{
    static const auto numOfSides = sizeof(eDirection);
    auto numOfCarsToMoveInIntersection = 0;
    auto minX = SCREEN_WIDTH;
    auto priorityCarToMove = cars.begin();
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        auto& car = *it;
        if (isCrossIntersection(car->getFuturePos())) {
            numOfCarsToMoveInIntersection++;
            // Запоминаем машину с минимальной координатой x
            if (car->m_rect.m_pos.m_x < minX) {
                minX = car->m_rect.m_pos.m_x;
                priorityCarToMove = it;
            }
        }
    }
    // Если на перекрестке стоят машины со всех 4х сторон, то первой проезжает машина, у которой минимальная координата по X
    if (numOfCarsToMoveInIntersection == numOfSides) {
        priorityCarToMove->get()->move();
        while (isCrossIntersection(priorityCarToMove->get()->getCurrentPos())) {
            if (priorityCarToMove->get()->getFuel()) {
                priorityCarToMove->get()->move();
            }
            else {
                priorityCarToMove->get()->refill(defaultFuel);
            }
        }
    }
}

void mainLoop() 
{
    while (true) {
        // Перед движением всех машин: проверка на ситуацию, когда машины со всех сторон могут заехать на перекресток
        checkMoveCarsFromAllSides();

        auto numCarSpawn = 0;
        for (auto it = cars.begin(); it != cars.end();) {
            auto& car = *it;
            // Проверка, может ли ехать текущая машина
            auto isMove = true;

            // Если текущая машина уже на перекрестке - она проезжает
            // Если машина попадает в перекресток после движения, необходима проверка для других машин
            if (!isCrossIntersection(car->getCurrentPos()) && isCrossIntersection(car->getFuturePos())) {
                for (auto& anotherCar : cars) {
                    if (car == anotherCar) {
                        continue;
                    }

                    // Если другая машина уже заехала на часть перекрестка, у нее приоритет проезда
                    // Для машин с противоположным направлением движения не нужно
                    if (!isOpossiteDirection(car->m_dir, anotherCar->m_dir) && isCrossIntersection(anotherCar->getCurrentPos())) {
                        isMove = false;
                        break;
                    }

                    // Другая машина также может заехать на перекресток
                    if (isCrossIntersection(anotherCar->getFuturePos())) {
                        if (car->needPassOtherCar(anotherCar.get())) {
                            isMove = false;
                            break;
                        }
                    }
                }
            }         

            if (isMove) {
                // Машина может проезжать
                if (car->getFuel()) {
                    car->move();
                }
                else {
                    // Заправляемся на этом ходу
                    car->refill(defaultFuel);
                }
            }

            // Удаление машины, которая вне области видимости экрана
            if ((car->m_rect.m_pos.m_x > SCREEN_WIDTH || car->m_rect.m_pos.m_x + car->m_rect.m_size.m_width < 0)
            || (car->m_rect.m_pos.m_y - car->m_rect.m_size.m_height > SCREEN_HEIGHT || car->m_rect.m_pos.m_y < 0)) {
                it = cars.erase(it);
                numCarSpawn++;
            }
            else {
                ++it;
            }
        }

        // После движения всех машин, необходима проверка на возможность создания машин в начальных положениях
        if (queueСarsToSpawn.size()) {
            trySpawnCarFromQueue();
        }

        // Создание новых машин, взамен удаленным
        while (numCarSpawn) {
            spawnCar();
            numCarSpawn--;
        }
    }
}

int main(int argc, char** argv) 
{
    srand(static_cast<unsigned int>(time(nullptr)));

    const int initialCarsCount = 10;
    for (auto i = 0; i < initialCarsCount; ++i) {
        spawnCar();
    }

    mainLoop();

    return 0;
}