from django.shortcuts import render, get_object_or_404
from django.http import HttpResponseRedirect
from django.urls import reverse
from django.utils import timezone
from .forms import RentalPropertyAddForm
from .models import RentingItem

# Create your views here.

def home(request):
    renting_items_list = RentingItem.objects.all()
    context = {'renting_items_list': renting_items_list}
    return render(request, 'rentalpropertyapp/home.html', context)

    #renting_items_list = RentingItem.objects.all()
    #template = loader.get_template('rentalpropertyapp/home.html')
    #context = {'renting_items_list': renting_items_list}
    #return HttpResponse(template.render(context, request))

    #renting_items_list = RentingItem.objects.all()
    #ri_list_prices = ([str(ri.price) for ri in renting_items_list])
    #ri_list_addresses = ([ri.address for ri in renting_items_list])
    #addresses_str = ', '.join(ri_list_addresses)
    #prices_str = ', '.join(ri_list_prices)
    #output = addresses_str + ' ' + prices_str
    #return HttpResponse(output)


def detail(request, rentingitem_id):
    renting_item = get_object_or_404(RentingItem, pk=rentingitem_id)
    return render(request, 'rentalpropertyapp/detail.html', {'renting_item': renting_item, 'title':rentingitem_id})

    #try:
    #    renting_item = RentingItem.objects.get(pk=rentingitem_id)
    #except RentingItem.DoesNotExist:
    #    raise Http404("RentingItem does not exist")
    #return render(request, 'rentalpropertyapp/detail.html', {'renting_item': renting_item})


def add(request):
    if request.method == 'POST':
        add_form = RentalPropertyAddForm(request.POST)
        if add_form.is_valid():
            price = add_form.cleaned_data['price']
            address = add_form.cleaned_data['address']
            ri = RentingItem(price=price, address=address, pub_date=timezone.now())
            ri.save()

        #price = request.POST.get('priceinput', None)
        #address = request.POST.get('addressinput', None)
        #ri = RentingItem(price=price, address=address, pub_date=timezone.now())
        #ri.save()

    return HttpResponseRedirect(reverse('rentalpropertyapp:rentalproperty-home'))

def delete(request, rentingitem_id):
    renting_item = get_object_or_404(RentingItem, pk=rentingitem_id)
    renting_item.delete()
    return HttpResponseRedirect(reverse('rentalpropertyapp:rentalproperty-home'))

# Examples:

# def detail(request, rentingitem_id):
#     return HttpResponse("You're looking at rentingitem_id %s." % rentingitem_id)
#
# def results(request, rentingitem_id):
#     response = "You're looking at the results of rentingitem_id %s."
#     return HttpResponse(response % rentingitem_id)
#
# def vote(request, rentingitem_id):
#     return HttpResponse("You're voting on rentingitem_id %s." % rentingitem_id)
