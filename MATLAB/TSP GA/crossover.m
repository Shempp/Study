function NewPopulation=crossover(OldPopulation, Pc)
if nargin==1
    Pc=0.5;
end

% Размер популяции
SizeOfPop=size(OldPopulation,1); 
% Количество пар для кроссовера
NumOfPares=floor(SizeOfPop/2);   
% Пары хромосом, выбранные случайно для скрещивания
SelPairsCros=rand(NumOfPares,1)<=Pc;  
NewPopulation=OldPopulation;

for i=1:NumOfPares
    Index=(i-1)*2+1;
    if ~(SelPairsCros(i)==0)
       % Первая хромосома из пары
       FirstChrom=OldPopulation(Index,:);
       % Вторая хромосома из пары
       SecondChrom=OldPopulation(Index+1,:);
       % Генераци¤ точки скрещивания
       CrossPoint=randi(length(FirstChrom));
       % Классический кроссовер
       FirstChild=[FirstChrom(1:CrossPoint) SecondChrom(CrossPoint+1:end)];
       SecondChild=[SecondChrom(1:CrossPoint) FirstChrom(CrossPoint+1:end)];
       % Меняем исходную популяцию
       NewPopulation(Index,:)=FirstChild;
       NewPopulation(Index+1,:)=SecondChild;
    end
end
