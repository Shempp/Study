from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='rentalproperty-home'),


    # ex: /rentalpropertyapp/5/
    #path('<int:rentingitem_id>/', views.detail, name='detail'),
    # ex: /rentalpropertyapp/5/results/
    #path('<int:rentingitem_id>/results/', views.results, name='results'),
    # ex: /rentalpropertyapp/5/vote/
    #path('<int:rentingitem_id>/vote/', views.vote, name='vote'),
]