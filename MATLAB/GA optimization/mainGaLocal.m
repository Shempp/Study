%% ����� ������� ������
clear
clc

%% �������� ��������� ��
% � ��������� ������������ ��������� ������������
% ������ ������� ����������� (x1, x2)
LowerBound=[-100 -100];
% ������� ������� ����������� (x1, x2)
UpperBound=[100 100];
% ��������� �����������
GAInputParams.SpaceIntervals=[LowerBound; UpperBound];
% ���������� �������� (����� ���������/���������)
GAInputParams.NumOfIterations=100;
% ���������� �������� (��� ������ - ��� ����� �������, �� ������ �� �������)
GAInputParams.SizeOfPopulation=1000;
% ��������� ��� ��������������� ���������� (�������� [0,1])
GAInputParams.Alpha=0.5;
                  
%% ���������� ��
GAResult=gaLocal(GAInputParams);

%% ���������� ��
disp("GA Optimization results:")
disp("Fxmin: " + num2str(GAResult.Fxmin))
disp("xmin: " + mat2str(GAResult.Xmin))

%% ������
plotEasomFunc(GAResult.Xmin, GAResult.Fxmin, GAResult.XminGen, GAResult.FxminGen)
