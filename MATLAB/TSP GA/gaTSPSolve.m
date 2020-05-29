function [GATour,GADistance] = gaTSPSolve(SizeOfPop,NumOfIter,DistanceMatrix,Pc,Pm)
% Примечание: данный генетический алгоритм для решения задачи коммивояжера 
% строится на основе упорядоченного представления/представления порядка 
% (ordinal representation).
% Данный вид представления использует классический кроссовер. 
% К сожалению, данный вид представления и ГА показывают посредственные
% результаты.

GATour=0;
GADistance=0;

% Количество вершин (городов)
NumOfPoints=length(DistanceMatrix);
% Дистанции каждой хромосомы популяции
DistancePopulation=zeros(1,SizeOfPop);

% Генерация путевых представлений, конвертация в представление порядка
Population=zeros(SizeOfPop,NumOfPoints);
% Первый путь будет простейшим последовательным списком точек
Path=1:NumOfPoints;
Population(1,:)=pathToOrder(Path);
% Остальные пути - случайная генерация
for i=2:SizeOfPop
    Path=randperm(NumOfPoints);
    Population(i,:)=pathToOrder(Path);
end

% Основной цикл ГА
for i=1:NumOfIter
    % Перед репродукцией выполняем подсчет дистанций текущей популяции
    for j=1:SizeOfPop
        Path=orderToPath(Population(j,:));
        DistancePopulation(j)=calcDistance(Path,DistanceMatrix);
    end
    % Репродукция
    Population=reproduction(DistancePopulation, Population);
    % Для путевого представления используем классический кроссовер
    Population=crossover(Population,Pc);
    % Случайная мутация (однородная)
    Population=mutation(Population,Pm);
end

% Выполняем подсчет дистанций итоговой популяции
for i=1:SizeOfPop
    Path=orderToPath(Population(i,:));
    DistancePopulation(i)=calcDistance(Path,DistanceMatrix);
end

% Ищем минимальную дистанцию
[GADistance,IndexOfMinDistance]=min(DistancePopulation);
% Получение пути, соответствующего минимальной дистанции
GATour=orderToPath(Population(IndexOfMinDistance,:));

end