function NewPopulation=reproduction(FuncValues,OldPopulation)
% ����������� ������ (��� ���������)
NormData=(FuncValues - min(FuncValues)) / (max(FuncValues) - min(FuncValues));
% �������� NaN � ������, ���� ��� ��������� ���������. �������
if isnan(NormData)
    NewPopulation=OldPopulation;
    return
end
% ����������� ������ (��������������� ��� ��������)
NormData=1-NormData;
% ���������
SumOfNormData=sum(NormData);
% ������� ����������� ��� RWS
SelProbsMin=NormData/SumOfNormData;
% �������� ������� �� RWS
Indexes = inf(length(SelProbsMin),1);
for i=1:length(SelProbsMin)
    Indexes(i)=RWS(SelProbsMin);
end
% �� ������ �������� ��������� �������� ��������� ����� �������
[Rows,Columns]=size(OldPopulation);
NewPopulation=zeros(Rows,Columns);
for i=1:Rows
    NewPopulation(i,:)=OldPopulation(Indexes(i),:);
end