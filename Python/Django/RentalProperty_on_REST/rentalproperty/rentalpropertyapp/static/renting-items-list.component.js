'use strict';

// Register `rentingItemsList` component, along with its associated controller and template
angular.
    module('rentalpropertyApp').
    component('rentingItemsList', {  // This name is what AngularJS uses to match to the `<renting-items-list>` element.
        template:
            '<ul>' +
              '<li ng-repeat="rentingItem in $ctrl.rentingItems">' +
                '<span>{{rentingItem.name}}</span>' +
                '<p>{{rentingItem.price}}</p>' +
                '<p>{{rentingItem.pub_date | date:\'dd/MM/yyyy HH:mm:ss\'}}</p>' +
              '</li>' +
            '</ul>',
        controller: function RentingItemsListController() {
            var currentDate = new Date();
            this.rentingItems = [
                {
                    name: 'Saint-Petersburg, st. Begovaya, 10',
                    price: '25000',
                    pub_date: currentDate,
                }, {
                    name: 'Saint-Petersburg, st. Begovaya, 11',
                    price: '20000',
                    pub_date: currentDate,
                }, {
                    name: 'Saint-Petersburg, st. Begovaya, 12',
                    price: '15000',
                    pub_date: currentDate,
                }
            ];
        }
    });