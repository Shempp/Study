function ResultPopulation=createRandPopulation(SizeOfPopulation,SpaceIntervals)
%% ��������� ���������
% ���������� ��������
NumOfColumns = size(SpaceIntervals,2);
% �������� ������� ���� [sizeOfPopulation X numOfColumn], �������� � ��������� (0,1)
RandomMatrix = rand(SizeOfPopulation,NumOfColumns);
% ������ �������� ����������� ������� �� ��������� (x1, x2)
SizeOfDimension=[-1 1]*SpaceIntervals;
DimensionValues=ones(SizeOfPopulation,1)*SizeOfDimension;
LowerBoundValues=ones(SizeOfPopulation,1)*SpaceIntervals(1,:);
% (.*) - ��������� ��������������� ���������
% ��������� ��������� ��������� � ����������� ���������
ResultPopulation=DimensionValues.*RandomMatrix+LowerBoundValues;
