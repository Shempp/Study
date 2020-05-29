function NewPopulation=crossover(OldPopulation, Pc, Alpha)
%% �������������� ���������
if nargin==1
    Pc = 0.5;
    Alpha = 0.5;
elseif nargin==2
    Alpha = 0.5;
end

% ������ ���������
SizeOfPop = size(OldPopulation,1); 
% ���������� ��� ��� ����������
NumOfPares = floor(SizeOfPop/2);   
% ���� ��������, ��������� �������� ��� �����������
SelPairsCros = rand(NumOfPares,1)<= Pc;  
NewPopulation=OldPopulation;

for i=1:NumOfPares
    Index=(i-1)*2+1;
    if ~(SelPairsCros(i)==0)
       % ������ ��������� �� ����
       FirstChrom=OldPopulation(Index,:);
       % ������ ��������� �� ����
       SecondChrom=OldPopulation(Index+1,:);
       % ������� ��������������� ���������� � ���������� �������
       FirstChild=Alpha*FirstChrom+(1-Alpha)*SecondChrom;
       SecondChild=Alpha*SecondChrom+(1-Alpha)*FirstChrom;
       % ������ �������� ���������
       NewPopulation(Index,:)=FirstChild;
       NewPopulation(Index+1,:)=SecondChild;
    end
end
