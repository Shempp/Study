function NewPopulation=crossover(OldPopulation, Pc, Alpha)
%% Арифметический кроссовер
if nargin==1
    Pc = 0.5;
    Alpha = 0.5;
elseif nargin==2
    Alpha = 0.5;
end

% Размер популяции
SizeOfPop = size(OldPopulation,1); 
% Количество пар для кроссовера
NumOfPares = floor(SizeOfPop/2);   
% Пары хромосом, выбранные случайно для скрещивания
SelPairsCros = rand(NumOfPares,1)<= Pc;  
NewPopulation=OldPopulation;

for i=1:NumOfPares
    Index=(i-1)*2+1;
    if ~(SelPairsCros(i)==0)
       % Первая хромосома из пары
       FirstChrom=OldPopulation(Index,:);
       % Вторая хромосома из пары
       SecondChrom=OldPopulation(Index+1,:);
       % Формула арифмитического кроссовера и полученные потомки
       FirstChild=Alpha*FirstChrom+(1-Alpha)*SecondChrom;
       SecondChild=Alpha*SecondChrom+(1-Alpha)*FirstChrom;
       % Меняем исходную популяцию
       NewPopulation(Index,:)=FirstChild;
       NewPopulation(Index+1,:)=SecondChild;
    end
end
