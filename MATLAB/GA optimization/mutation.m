function NewPopulation=mutation(OldPopulation,SpaceIntervals,Pm)
%% ��������� ������� (����������)
SizeOfPopulation=size(OldPopulation,1);
% ���������, ��������� ��� �������
SelChromMut = rand(SizeOfPopulation,1)<=Pm;
NewPopulation=OldPopulation;

for i=1:SizeOfPopulation
    if ~(SelChromMut(i)==0)
        % ����� ���������� ���� ���������
        chooseGen=randi(length(SpaceIntervals));
        % ��������� ���������� ����� � ���������
        LowerBound=SpaceIntervals(1,1);
        UpperBound=SpaceIntervals(2,1);
        randValue=(UpperBound-LowerBound)*rand(1)+LowerBound;
        % ������ �������� ���������
        NewPopulation(i,chooseGen)=randValue;
    end
end