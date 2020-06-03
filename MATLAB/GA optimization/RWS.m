function Index=RWS(SelProbs)
%% Колесо рулетки (Roulette Wheel Selection) 
lenOfProbs=length(SelProbs);
if lenOfProbs==1
    Index=1;
    return;
end

if (~isempty(find(SelProbs<1, 1)))
    if (min(SelProbs)~=0)
        SelProbs=1/min(SelProbs)*SelProbs;
    else
        temp=SelProbs;
        temp(SelProbs==0)=inf;
        SelProbs=1/min(temp)*SelProbs;
    end
end

temp=0;
tempProb=zeros(1,lenOfProbs);

for i=1:lenOfProbs
    tempProb(i)=temp+SelProbs(i);
    temp=tempProb(i);
end

i=fix(rand*floor(tempProb(end)))+1;
Index=find(tempProb>=i, 1);
