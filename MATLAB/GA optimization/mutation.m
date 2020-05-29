function NewPopulation=mutation(OldPopulation,SpaceIntervals,Pm)
%% Случайная мутация (однородная)
SizeOfPopulation=size(OldPopulation,1);
% Хромосомы, выбранные для мутации
SelChromMut = rand(SizeOfPopulation,1)<=Pm;
NewPopulation=OldPopulation;

for i=1:SizeOfPopulation
    if ~(SelChromMut(i)==0)
        % Выбор случайного гена хромосомы
        chooseGen=randi(length(SpaceIntervals));
        % Получение случайного числа в интервале
        LowerBound=SpaceIntervals(1,1);
        UpperBound=SpaceIntervals(2,1);
        randValue=(UpperBound-LowerBound)*rand(1)+LowerBound;
        % Меняем исходную популяцию
        NewPopulation(i,chooseGen)=randValue;
    end
end