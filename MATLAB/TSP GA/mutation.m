function NewPopulation=mutation(OldPopulation,Pm)
[SizeOfPopulation,SizeOfChrom]=size(OldPopulation);
% ���������, ��������� ��� �������
SelChromMut = rand(SizeOfPopulation,1)<=Pm;
NewPopulation=OldPopulation;
for i=1:SizeOfPopulation
    if ~(SelChromMut(i)==0)
        % ����� ���������� ���� ���������
        ChooseGen=randi(SizeOfChrom);
        % ��������� ���������� ����� ��� �������
        % ����� ���������� ���������, ��� i-� ������� ������ � ���
        % ����� �� 1 �� n-i+1
        RandValue=randi(SizeOfChrom-ChooseGen+1);
        % ������ �������� ���������
        NewPopulation(i,ChooseGen)=RandValue;
    end
end
