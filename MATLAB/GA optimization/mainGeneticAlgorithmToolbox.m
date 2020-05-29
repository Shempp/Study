% ����� ������� ������
clear
clc
% �������� �������
ObjectiveFunction = @easomFunction;
% ����� ����������
nvars = 3;   
% ������ �������
LB = [-100 -100]; 
% ������� �������
UB = [100 100]; 
% gaplotbestf - ���������� ������ � ������� ��������� � ������ ���������
% gaplotstopping - ���������� �������, ����� ��������� ��������� ���������
% gaplotscorediversity - ������ ����������� ���������� ��������
% �� ������������� �������� �� ������� ���������
% selectionroulette - ���������� ��� �������� ������� (RWS)
% CrossoverFraction - ����������� �������������
% crossoverarithmetic - ���������� �������������� ���������
% mutationuniform, rate - ����������� ������� + ����������� �������
% Display - ����������� ��������
% iter - ����������� �� ������ �������� (0.01)

%'CrossoverFraction', 0.8, ...
%'MutationFcn', {@mutationuniform, 0.1}, ...
options = optimoptions(@ga, ...
    'PlotFcn',{@gaplotbestf,@gaplotstopping,@gaplotscorediversity}, ...
    'SelectionFcn',@selectionroulette, ...
    'CrossoverFcn',@crossoverarithmetic, ...
    'Display','iter');
% ���������� �������� � ���������
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

% ������ easom's function � ����������� � ������� ���������
plotEasomFunc(X, Fx, Population, Scores)
