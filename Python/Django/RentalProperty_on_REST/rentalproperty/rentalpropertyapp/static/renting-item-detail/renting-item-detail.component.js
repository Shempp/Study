'use strict';

angular.
    module('rentingItemDetail').
    component('rentingItemDetail', {
        templateUrl: '/static/renting-item-detail/renting-item-detail.template.html',
        controller: ['$routeParams', '$http', '$location', function RentingItemDetailController($routeParams, $http, $location) {
            var self = this;
            var homeURL = 'http://127.0.0.1:8000/api/rentingitems/';
            var detailURL = homeURL + $routeParams.rentingItemId + '/';
            // REST HTTP GET
            $http.get(detailURL).then(function(response) {
                //self.id = response.data.id;
                self.address = response.data.address;
                self.price = response.data.price;
                self.pub_date = response.data.pub_date;
            });

            // Register callback deleteRentingItem for deleting RentingItem
            self.deleteRentingItem = function() {
                $http.delete(detailURL).then(function(response) {
                    // Redirect to home page
                    $location.url(homeURL);
                });
            }
        }]
    });
