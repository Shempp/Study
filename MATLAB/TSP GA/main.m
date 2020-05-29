% ����� ������� ������
clc
clear

% ������� ������� ���������� ���������
tic

% ������� �������� ������
% ��������� ���������� berlin52
EucCoords = dlmread('Euclidean�oordinates-berlin52.txt');
X=EucCoords(:,1);
Y=EucCoords(:,2);
% ������ ��� berlin52
OptTour = dlmread('OptimumTour-berlin52.txt');
% ������� ���������� ��������� � ������� ���������
DistanceMatrix=coordsToMatrix(X,Y);

% ���������� ������������ ���������� �� ������� ����
OptimalDistance=calcDistance(OptTour,DistanceMatrix);
% ������ ������������ (�������) �������
plotTour(OptTour,OptimalDistance,EucCoords);

% ��������� ��
% ������ ���������
SizeOfPop=100;
% ���������� ��������
NumOfIter=1000;
% ����������� ����������
Pc=0.5;
% ����������� �������
Pm=0.1;
% ���������� ������������� ���������
[GATour,GADistance]=gaTSPSolve(SizeOfPop,NumOfIter,DistanceMatrix,Pc,Pm);
disp("Tour="+mat2str(GATour));
disp("Distance="+GADistance);

% ������ ������������� �������
plotTour(GATour,GADistance,EucCoords);

% ������� ������� ���������� ���������
TimeElapsed=toc;
disp("Time execution of program="+sprintf('%.4f',TimeElapsed));
