function NewPopulation=crossover(OldPopulation, Pc)
if nargin==1
    Pc=0.5;
end

% –азмер попул¤ции
SizeOfPop=size(OldPopulation,1); 
%  оличество пар дл¤ кроссовера
NumOfPares=floor(SizeOfPop/2);   
% ѕары хромосом, выбранные случайно дл¤ скрещивани¤
SelPairsCros=rand(NumOfPares,1)<=Pc;  
NewPopulation=OldPopulation;

for i=1:NumOfPares
    Index=(i-1)*2+1;
    if ~(SelPairsCros(i)==0)
       % ѕерва¤ хромосома из пары
       FirstChrom=OldPopulation(Index,:);
       % ¬тора¤ хромосома из пары
       SecondChrom=OldPopulation(Index+1,:);
       % √енераци¤ точки скрещивани¤
	   CrossPoint=randi(length(FirstChrom));
       %  лассический кроссовер
       FirstChild=[FirstChrom(1:CrossPoint) SecondChrom(CrossPoint+1:end)];
       SecondChild=[SecondChrom(1:CrossPoint) FirstChrom(CrossPoint+1:end)];
       % ћен¤ем исходную попул¤цию
       NewPopulation(Index,:)=FirstChild;
       NewPopulation(Index+1,:)=SecondChild;
    end
end
