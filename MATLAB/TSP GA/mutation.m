function NewPopulation=mutation(OldPopulation,Pm)
[SizeOfPopulation,SizeOfChrom]=size(OldPopulation);
% Хромосомы, выбранные для мутации
SelChromMut = rand(SizeOfPopulation,1)<=Pm;
NewPopulation=OldPopulation;
for i=1:SizeOfPopulation
    if ~(SelChromMut(i)==0)
        % Выбор случайного гена хромосомы
        ChooseGen=randi(SizeOfChrom);
        % Получение случайного числа для мутации
        % Здесь необходимо учитывать, что i-й элемент списка – это
        % номер от 1 до n-i+1
        RandValue=randi(SizeOfChrom-ChooseGen+1);
        % Меняем исходную популяцию
        NewPopulation(i,ChooseGen)=RandValue;
    end
end
