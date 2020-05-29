function NewPopulation=crossover(OldPopulation, Pc)
if nargin==1
    Pc=0.5;
end

% ������ ���������
SizeOfPop=size(OldPopulation,1); 
% ���������� ��� ��� ����������
NumOfPares=floor(SizeOfPop/2);   
% ���� ��������, ��������� �������� ��� �����������
SelPairsCros=rand(NumOfPares,1)<=Pc;  
NewPopulation=OldPopulation;

for i=1:NumOfPares
    Index=(i-1)*2+1;
    if ~(SelPairsCros(i)==0)
       % ������ ��������� �� ����
       FirstChrom=OldPopulation(Index,:);
       % ������ ��������� �� ����
       SecondChrom=OldPopulation(Index+1,:);
       % ��������� ����� �����������
	   CrossPoint=randi(length(FirstChrom));
       % ������������ ���������
       FirstChild=[FirstChrom(1:CrossPoint) SecondChrom(CrossPoint+1:end)];
       SecondChild=[SecondChrom(1:CrossPoint) FirstChrom(CrossPoint+1:end)];
       % ������ �������� ���������
       NewPopulation(Index,:)=FirstChild;
       NewPopulation(Index+1,:)=SecondChild;
    end
end
