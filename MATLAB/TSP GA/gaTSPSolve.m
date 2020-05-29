function [GATour,GADistance] = gaTSPSolve(SizeOfPop,NumOfIter,DistanceMatrix,Pc,Pm)
% ����������: ������ ������������ �������� ��� ������� ������ ������������ 
% �������� �� ������ �������������� �������������/������������� ������� 
% (ordinal representation).
% ������ ��� ������������� ���������� ������������ ���������. 
% � ���������, ������ ��� ������������� � �� ���������� ��������������
% ����������.

GATour=0;
GADistance=0;

% ���������� ������ (�������)
NumOfPoints=length(DistanceMatrix);
% ��������� ������ ��������� ���������
DistancePopulation=zeros(1,SizeOfPop);

% ��������� ������� �������������, ����������� � ������������� �������
Population=zeros(SizeOfPop,NumOfPoints);
% ������ ���� ����� ���������� ���������������� ������� �����
Path=1:NumOfPoints;
Population(1,:)=pathToOrder(Path);
% ��������� ���� - ��������� ���������
for i=2:SizeOfPop
    Path=randperm(NumOfPoints);
    Population(i,:)=pathToOrder(Path);
end

% �������� ���� ��
for i=1:NumOfIter
    % ����� ������������ ��������� ������� ��������� ������� ���������
    for j=1:SizeOfPop
        Path=orderToPath(Population(j,:));
        DistancePopulation(j)=calcDistance(Path,DistanceMatrix);
    end
    % �����������
    Population=reproduction(DistancePopulation, Population);
    % ��� �������� ������������� ���������� ������������ ���������
    Population=crossover(Population,Pc);
    % ��������� ������� (����������)
    Population=mutation(Population,Pm);
end

% ��������� ������� ��������� �������� ���������
for i=1:SizeOfPop
    Path=orderToPath(Population(i,:));
    DistancePopulation(i)=calcDistance(Path,DistanceMatrix);
end

% ���� ����������� ���������
[GADistance,IndexOfMinDistance]=min(DistancePopulation);
% ��������� ����, ���������������� ����������� ���������
GATour=orderToPath(Population(IndexOfMinDistance,:));

end