from django.shortcuts import render

# Create your views here.

from django.http import HttpResponse
from .models import RentingItem
from django.template import loader

def home(request):
    renting_items_list = RentingItem.objects.all()
    template = loader.get_template('rentalpropertyapp/index.html')
    context = {
        'renting_items_list': renting_items_list,
    }
    return HttpResponse(template.render(context, request))

    #renting_items_list = RentingItem.objects.all()
    #ri_list_prices = ([str(ri.price) for ri in renting_items_list])
    #ri_list_addresses = ([ri.address for ri in renting_items_list])
    #addresses_str = ', '.join(ri_list_addresses)
    #prices_str = ', '.join(ri_list_prices)
    #output = addresses_str + ' ' + prices_str
    #return HttpResponse(output)

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