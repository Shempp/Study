function GADat=performGAIteration(GADat)
%% Полная итерация ГА
Population=GADat.Population;
SizeOfPopulation=size(Population,1);

% Вычисления значений заданной функции
FuncValues=inf(SizeOfPopulation,1);
for i=1:SizeOfPopulation
    FuncValues(i)=easomFunction(Population(i,:));
end
GADat.FuncValues=FuncValues;

% Поиск лучшей хромосомы популяции
[Value,Index]=min(GADat.FuncValues);
if Value<=GADat.Fxmin
    GADat.Xmin=Population(Index,:);
    GADat.Fxmin=Value;
end

% Вывод результатов текущей итерации
printIteration(GADat);
% Репродукция
Population=reproduction(GADat.FuncValues, Population);
% Кроссинговер (арифметический кроссовер)
Population=crossover(Population,GADat.Pc,GADat.Alpha);
% Случайная мутация
Population=mutation(Population,GADat.SpaceIntervals,GADat.Pm);
% Вставим лучшую особь в популяцию (сратегия элитизма)
Population(round(GADat.SizeOfPopulation/2),:)=GADat.Xmin;
GADat.Population=Population;