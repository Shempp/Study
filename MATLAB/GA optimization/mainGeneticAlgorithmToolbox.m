% Перед началом работы
clear
clc
% Заданная функция
ObjectiveFunction = @easomFunction;
% Число переменных
nvars = 3;   
% Нижние границы
LB = [-100 -100]; 
% Верхние границы
UB = [100 100]; 
% gaplotbestf - показывает лучший и средний результат в каждой популяции
% gaplotstopping - показывает процент, когда критериев остановки выполнены
% gaplotscorediversity - строит гистограмму количества хромосом
% по определенному значению по каждому поколению
% selectionroulette - использует для селекции рулетку (RWS)
% CrossoverFraction - вероятность кроссинговера
% crossoverarithmetic - использует арифмитический кроссовер
% mutationuniform, rate - равномерная мутация + вероятность мутации
% Display - отображение диаграмм
% iter - отображение на каждой итерации (0.01)

%'CrossoverFraction', 0.8, ...
%'MutationFcn', {@mutationuniform, 0.1}, ...
options = optimoptions(@ga, ...
    'PlotFcn',{@gaplotbestf,@gaplotstopping,@gaplotscorediversity}, ...
    'SelectionFcn',@selectionroulette, ...
    'CrossoverFcn',@crossoverarithmetic, ...
    'Display','iter');
% Количество хромосом в популяции
options.PopulationSize=1000;

[X,Fx,Exitflag,Output,Population,Scores] = ga(ObjectiveFunction,nvars,[],[],[],[],LB,UB,...
    [], options);

disp('Result of GA:');
disp('1. x1,x2=');
disp(X);
disp('1. Fx=');
disp(Fx);
disp('1. ExitFlag=');
disp(Exitflag);
disp('1. Output=');
disp(Output);
disp('1. Population=');
disp(Population);
disp('1. Scores=');
disp(Scores);

% График easom's function с экстремумом и точками популяции
plotEasomFunc(X, Fx, Population, Scores)
