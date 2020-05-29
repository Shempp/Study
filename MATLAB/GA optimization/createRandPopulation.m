function ResultPopulation=createRandPopulation(SizeOfPopulation,SpaceIntervals)
%% Генерация популяции
% Количество столбцов
NumOfColumns = size(SpaceIntervals,2);
% Создание матрицы вида [sizeOfPopulation X numOfColumn], значения в интервале (0,1)
RandomMatrix = rand(SizeOfPopulation,NumOfColumns);
% Вектор значений размерности каждого из измерений (x1, x2)
SizeOfDimension=[-1 1]*SpaceIntervals;
DimensionValues=ones(SizeOfPopulation,1)*SizeOfDimension;
LowerBoundValues=ones(SizeOfPopulation,1)*SpaceIntervals(1,:);
% (.*) - умножение соответствующих элементов
% Получение случайной популяции в необходимом интервале
ResultPopulation=DimensionValues.*RandomMatrix+LowerBoundValues;
