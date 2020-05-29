function NewPopulation=mutation(OldPopulation,Pm)
[SizeOfPopulation,SizeOfChrom]=size(OldPopulation);
% ’ромосомы, выбранные дл¤ мутации
SelChromMut = rand(SizeOfPopulation,1)<=Pm;
NewPopulation=OldPopulation;
for i=1:SizeOfPopulation
    if ~(SelChromMut(i)==0)
        % ¬ыбор случайного гена хромосомы
        ChooseGen=randi(SizeOfChrom);
        % ѕолучение случайного числа дл¤ мутации
        % «десь необходимо учитывать, что i-й элемент списка Ц это
        % номер от 1 до n-i+1
        RandValue=randi(SizeOfChrom-ChooseGen+1);
        % ћен¤ем исходную попул¤цию
        NewPopulation(i,ChooseGen)=RandValue;
    end
end
