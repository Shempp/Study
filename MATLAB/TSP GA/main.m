% Перед началом работы
clc
clear

% Подсчет времени выполнения программы
tic

% Вычитка исходных данных
% Евклидовы координаты berlin52
EucCoords = dlmread('Euclidean�oordinates-berlin52.txt');
X=EucCoords(:,1);
Y=EucCoords(:,2);
% Лучший тур berlin52
OptTour = dlmread('OptimumTour-berlin52.txt');
% Перевод евклидовых координат в матрицу дистанций
DistanceMatrix=coordsToMatrix(X,Y);

% Вычисление оптимального расстояния по лучшему туру
OptimalDistance=calcDistance(OptTour,DistanceMatrix);
% График оптимального (лучшего) решения
plotTour(OptTour,OptimalDistance,EucCoords);

% Параметры ГА
% Размер популяции
SizeOfPop=100;
% Количество итераций
NumOfIter=1000;
% Вероятность кроссовера
Pc=0.5;
% Вероятность мутации
Pm=0.1;
% Выполнение генетического алгоритма
[GATour,GADistance]=gaTSPSolve(SizeOfPop,NumOfIter,DistanceMatrix,Pc,Pm);
disp("Tour="+mat2str(GATour));
disp("Distance="+GADistance);

% График получившегося решения
plotTour(GATour,GADistance,EucCoords);

% Подсчет времени выполнения программы
TimeElapsed=toc;
disp("Time execution of program="+sprintf('%.4f',TimeElapsed));
