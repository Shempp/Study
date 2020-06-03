%%% Основная функция ГА
function GAResult=gaLocal(InputParams) 
%% Инициализация
% Проверка на входные аргументы
if nargin==1
    GAResult=InputParams;
else
    error('Error: no input params')
end

%% Установка значений по-умолчанию, если не заданы во вх. данных
% Размерность пространства
if ~isfield(GAResult,'DimensionSpace')
    % В случае двумерного пространства, это количество столбцов матрицы
    GAResult.DimensionSpace=size(GAResult.SpaceIntervals,2);
end
% Размер популяции (число особей)
if ~isfield(GAResult,'SizeOfPopulation')
    GAResult.SizeOfPopulation=GAResult.NVAR*50;
end
% Количество поколений (генераций)
if ~isfield(GAResult,'NumOfIterations')
    GAResult.NumOfIterations=GAResult.NVAR*20+10;
end
% Вероятность кроссинговера (скрещивания)
if ~isfield(GAResult,'Pc')
    GAResult.Pc=0.5;
end
% Вероятность мутации
if ~isfield(GAResult,'Pm')
    GAResult.Pm=0.1;
end
% Константа для арифмитического кроссовера (интервал [0,1])
if ~isfield(GAResult,'Alpha')
    GAResult.Alpha=0.5;
end

%% Инициализация внутренних параметров
% Популяция в текущей итерации
GAResult.Population=[];
% Значения заданной функции в текущей итерации
GAResult.FuncValues=[];
% Минимальное значение аргументов функции в текущей итерации
GAResult.Xmin=[];
% Минимальное значение функции в текущей итерации
GAResult.Fxmin=inf;
% Минимальные значения аргументов функции на каждой итерации
GAResult.XminGen=[];
% Минимальные значения функции на каждой итерации
GAResult.FxminGen=[];
% Текущий номер поколения
GAResult.Generation=0;

%% Начало работы алгоритма
% Счетчик поколений
CurrentGeneration=0;
% Генерация начальной популяции
GAResult.Population=createRandPopulation(GAResult.SizeOfPopulation,GAResult.SpaceIntervals);  

% Главный цикл алгоритма
while (GAResult.Generation<GAResult.NumOfIterations)
    GAResult.Generation=CurrentGeneration;
    GAResult=performGAIteration(GAResult);     
    GAResult.XminGen(CurrentGeneration+1,:)=GAResult.Xmin;
    GAResult.FxminGen(CurrentGeneration+1,:)=GAResult.Fxmin;
    CurrentGeneration=CurrentGeneration+1;
end
