/*
 * Intel Low Power Subsystem clocks.
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.intel.com>
 *	    Heikki Krogerus <heikki.krogerus@linux.intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk-provider.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/platform_data/x86/clk-lpss.h>
#include <linux/platform_device.h>

static int lpss_atom_clk_probe(struct platform_device *pdev)
{
	struct lpss_clk_data *drvdata;
	struct clk *clk;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	/* LPSS free running clock */
	drvdata->name = "lpss_clk";
	clk = clk_register_fixed_rate(&pdev->dev, drvdata->name, NULL,
				      0, 100000000);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	drvdata->clk = clk;
	platform_set_drvdata(pdev, drvdata);
	return 0;
}

static struct platform_driver lpss_atom_clk_driver = {
	.driver = {
		.name = "clk-lpss-atom",
	},
	.probe = lpss_atom_clk_probe,
};

int __init lpss_atom_clk_init(void)
{
	return platform_driver_register(&lpss_atom_clk_driver);
}
