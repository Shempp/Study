'use strict';

// Register `rentingItemsList` component on the 'rentingItemsList' module
angular.
    module('rentingItemsList').
    component('rentingItemsList', {  // This name is what AngularJS uses to match to the `<renting-items-list>` element.
        // Note: The URL is relative to our `home.html` file
        templateUrl: '/static/renting-items-list/renting-items-list.template.html',
        controller: ['$http', function RentingItemsListController($http) {
                var self = this;
                self.orderProp = 'price';
                self.addressToAdd = '';

                // REST HTTP GET
                $http.get('http://127.0.0.1:8000/api/rentingitems/').then(function(response) {
                    self.rentingItems = response.data;
                });

                /*
                // Make http request to server to fetch the data in json file
                // For tests
                $http.get('/static/RentingItems.json').then(function(response) {
                    self.rentingItems = response.data;
                });
                 */

                /*
                var currentDate = new Date();
                this.rentingItems = [
                    {
                        address: 'Saint-Petersburg, st. Begovaya, 10',
                        price: '25000',
                        pub_date: currentDate,
                    }, {
                        address: 'Saint-Petersburg, st. Begovaya, 11',
                        price: '20000',
                        pub_date: currentDate,
                    }, {
                        address: 'Saint-Petersburg, st. Begovaya, 12',
                        price: '15000',
                        pub_date: currentDate,
                    } , {
                        address: 'Anapa, st. Pushkina, 1',
                        price: '9000',
                        pub_date: currentDate,
                    }
                ];
                this.orderProp = 'price';
                 */
        }]
    });