from django.urls import path
from . import views

app_name = 'rentalpropertyapp'
urlpatterns = [
    # ex: /rentalpropertyapp/
    path('', views.home, name='rentalproperty-home'),
    # ex: /rentalpropertyapp/5/
    path('<int:rentingitem_id>/', views.detail, name='rentalproperty-detail'),
    # ex: /rentalpropertyapp/add
    path('add', views.add, name='rentalproperty-add'),
    # ex: /rentalpropertyapp/delete/5/
    path('delete/<int:rentingitem_id>/', views.delete, name='rentalproperty-delete'),

    # Examples:
    # ex: /rentalpropertyapp/5/
    #path('<int:rentingitem_id>/', views.detail, name='detail'),
    # ex: /rentalpropertyapp/5/results/
    #path('<int:rentingitem_id>/results/', views.results, name='results'),
    # ex: /rentalpropertyapp/5/vote/
    #path('<int:rentingitem_id>/vote/', views.vote, name='vote'),
]