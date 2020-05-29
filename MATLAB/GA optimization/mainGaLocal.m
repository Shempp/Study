%% Перед началом работы
clear
clc

%% Основные параметры ГА
% В программе используется двумерное пространство
% Нижние границы пространств (x1, x2)
LowerBound=[-100 -100];
% Верхние границы пространств (x1, x2)
UpperBound=[100 100];
% Интервалы пространств
GAInputParams.SpaceIntervals=[LowerBound; UpperBound];
% Количество итераций (число поколений/генераций)
GAInputParams.NumOfIterations=100;
% Количество хромосом (чем больше - тем лучше решение, но дольше по времени)
GAInputParams.SizeOfPopulation=1000;
% Константа для арифмитического кроссовера (интервал [0,1])
GAInputParams.Alpha=0.5;
                  
%% Выполнение ГА
GAResult=gaLocal(GAInputParams);

%% Результаты ГА
disp("GA Optimization results:")
disp("Fxmin: " + num2str(GAResult.Fxmin))
disp("xmin: " + mat2str(GAResult.Xmin))

%% График
plotEasomFunc(GAResult.Xmin, GAResult.Fxmin, GAResult.XminGen, GAResult.FxminGen)
