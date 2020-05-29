function GADat=performGAIteration(GADat)
%% ������ �������� ��
Population=GADat.Population;
SizeOfPopulation=size(Population,1);

% ���������� �������� �������� �������
FuncValues=inf(SizeOfPopulation,1);
for i=1:SizeOfPopulation
    FuncValues(i)=easomFunction(Population(i,:));
end
GADat.FuncValues=FuncValues;

% ����� ������ ��������� ���������
[Value,Index]=min(GADat.FuncValues);
if Value<=GADat.Fxmin
    GADat.Xmin=Population(Index,:);
    GADat.Fxmin=Value;
end

% ����� ����������� ������� ��������
printIteration(GADat);
% �����������
Population=reproduction(GADat.FuncValues, Population);
% ������������ (�������������� ���������)
Population=crossover(Population,GADat.Pc,GADat.Alpha);
% ��������� �������
Population=mutation(Population,GADat.SpaceIntervals,GADat.Pm);
% ������� ������ ����� � ��������� (�������� ��������)
Population(round(GADat.SizeOfPopulation/2),:)=GADat.Xmin;
GADat.Population=Population;