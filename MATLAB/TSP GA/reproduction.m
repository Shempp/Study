function NewPopulation=reproduction(FuncValues,OldPopulation)
% Нормализуем данные (для максимума)
NormData=(FuncValues - min(FuncValues)) / (max(FuncValues) - min(FuncValues));
% Получаем NaN в случае, если вся популяция одинакова. Выходим
if isnan(NormData)
    NewPopulation=OldPopulation;
    return
end
% Нормализуем данные (преобразовываем для минимума)
NormData=1-NormData;
% Суммируем
SumOfNormData=sum(NormData);
% Считаем вероятности для RWS
SelProbsMin=NormData/SumOfNormData;
% Получаем индексы от RWS
Indexes = inf(length(SelProbsMin),1);
for i=1:length(SelProbsMin)
    Indexes(i)=RWS(SelProbsMin);
end
% На основе индексов заполняем исходную популяцию после рулетки
[Rows,Columns]=size(OldPopulation);
NewPopulation=zeros(Rows,Columns);
for i=1:Rows
    NewPopulation(i,:)=OldPopulation(Indexes(i),:);
end